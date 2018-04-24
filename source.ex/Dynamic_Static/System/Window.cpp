
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/OpenGL.hpp"
#include "Dynamic_Static/System/Window.hpp"

#include "GLFW/glfw3.h"

#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>

namespace Dynamic_Static {
namespace System {

    static std::set<GLFWwindow*> sGlfwWindowHandles;
    static Window& dst_window(GLFWwindow* glfwWindowHandle);
    static GLFWwindow* glfw_handle(const void* glfwWindowHandle);
    static GLFWwindow* create_glfw_window(const Window::Info& windowInfo);
    static void destroy_glfw_window(GLFWwindow* glfwWindowHandle);

    Window::Window(const Info& info)
    {
        mHandle = create_glfw_window(info);
        glfwSetWindowUserPointer(glfw_handle(mHandle), this);
        // set cursor mode
        // set position
        // set visibility
        // set name
    }

    Window::Window(Window&& other)
    {
        *this = std::move(other);
    }

    Window::~Window()
    {
        destroy_glfw_window(glfw_handle(mHandle));
    }

    Window& Window::operator=(Window&& other)
    {
        if (this != &other) {
            mInfo = std::move(other.mInfo);
            mName = std::move(other.mName);
            mHandle = std::move(other.mHandle);
            mTextStream = std::move(other.mTextStream);
            mClipBoard = std::move(other.mClipBoard);
            other.mHandle = nullptr;
        }

        return *this;
    }

    const std::string& Window::get_name() const
    {
        return std::string("TODO");
    }

    void Window::set_name(const std::string& name)
    {
    }

    void Window::swap_buffers() const
    {
        #if DYNAMIC_STATIC_OPENGL_ENABLED
        if (mInfo.api == GraphicsApi::OpenGL) {
            glfwSwapBuffers(glfw_handle(mHandle));
        }
        #endif
    }

    void Window::poll_events()
    {
        glfwPollEvents();
    }

    Window& dst_window(GLFWwindow* glfwWindowHandle)
    {
        auto pWindow = glfwGetWindowUserPointer(glfwWindowHandle);
        assert(pWindow);
        return *static_cast<Window*>(pWindow);
    }

    GLFWwindow* glfw_handle(const void* glfwWindowHandle)
    {
        return reinterpret_cast<GLFWwindow*>(const_cast<void*>(glfwWindowHandle));
    }

    GLFWwindow* create_glfw_window(const Window::Info& windowInfo)
    {
        if (sGlfwWindowHandles.empty()) {
            glfwSetErrorCallback(glfw_error_callback);
            glfwInit();
            switch (windowInfo.api) {
                #if DYNAMIC_STATIC_OPENGL_ENABLED
                case GraphicsApi::OpenGL:
                {
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowInfo.apiVersion.major);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowInfo.apiVersion.minor);
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                } break;
                #endif

                #if DYNAMIC_STATIC_VULKAN_ENABLED
                case GraphicsApi::Vulkan:
                #endif

                default:
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            }
        }

        glfwWindowHint(GLFW_VISIBLE, windowInfo.visible);
        glfwWindowHint(GLFW_DECORATED, windowInfo.decorated);
        glfwWindowHint(GLFW_RESIZABLE, windowInfo.resizable);
        GLFWwindow* glfwWindowHandle = nullptr;
        try {
            glfwWindowHandle = glfwCreateWindow(
                windowInfo.resolution.x,
                windowInfo.resolution.y,
                windowInfo.name ? windowInfo.name : "",
                nullptr,
                windowInfo.parent ? nullptr : nullptr
            );
        } catch (const std::exception& e) {
            destroy_glfw_window(glfwWindowHandle);
        }

        #if DYNAMIC_STATIC_OPENGL_ENABLED
        if (windowInfo.api == GraphicsApi::OpenGL) {
            static bool sGLEWInitialized;
            if (!sGLEWInitialized) {
                glfwMakeContextCurrent(glfwWindowHandle);
                #if DYNAMIC_STATIC_WINDOWS
                glewExperimental = true;
                auto error = glewInit();
                if (error) {
                    destroy_glfw_window(glfwWindowHandle);
                    std::stringstream strStrm;
                    strStrm << glewGetErrorString(error);
                    throw std::runtime_error(strStrm.str());
                }
                #endif
                sGLEWInitialized = true;
            }

            if (windowInfo.vsync) {
                glfwSwapInterval(1);
            }
        }
        #endif

        glfwSetKeyCallback(glfwWindowHandle, glfw_key_callback);
        glfwSetFramebufferSizeCallback(glfwWindowHandle, glfw_framebuffer_size_callback);
        glfwSetMouseButtonCallback(glfwWindowHandle, glfw_mouse_button_callback);
        glfwSetCursorPosCallback(glfwWindowHandle, glfw_cursor_pos_callback);
        glfwSetScrollCallback(glfwWindowHandle, glfw_scroll_callback);
        glfwSetCharCallback(glfwWindowHandle, glfw_char_callback);
        return *sGlfwWindowHandles.insert(glfwWindowHandle).first;
    }

    void destroy_glfw_window(GLFWwindow* glfwWindowHandle)
    {
        if (glfwWindowHandle) {
            glfwDestroyWindow(glfwWindowHandle);
        }

        sGlfwWindowHandles.erase(glfwWindowHandle);
        if (sGlfwWindowHandles.empty()) {
            glfwTerminate();
        }
    }

    void glfw_key_callback(GLFWwindow* glfwWindowHandle, int glfwKey, int scanCode, int action, int mods)
    {
    }

    void glfw_framebuffer_size_callback(GLFWwindow* glfwWindowHandle, int width, int height)
    {
    }

    void glfw_mouse_button_callback(GLFWwindow* glfwWindowHandle, int glfwButton, int action, int mods)
    {
    }

    void glfw_cursor_pos_callback(GLFWwindow* glfwWindowHandle, double xOffset, double yOffset)
    {
    }

    void glfw_scroll_callback(GLFWwindow* glfwWindowHandle, double xOffset, double yOffset)
    {
    }

    void glfw_char_callback(GLFWwindow* glfwWindowHandle, unsigned int codepoint)
    {
    }

    void glfw_error_callback(int error, const char* description)
    {
        thread_local std::stringstream tlStrStrm;
        tlStrStrm.clear();
        tlStrStrm << "GLFW Error " << "[" << error << ":" << description << "]";
        throw std::runtime_error(tlStrStrm.str());
    }

} // namespace System
} // namespace Dynamic_Static
