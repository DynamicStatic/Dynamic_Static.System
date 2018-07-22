
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)

#include "Dynamic_Static/System/GLFW.hpp"
#include "Dynamic_Static/System/Window/Window.hpp"

#include <utility>

namespace Dynamic_Static {
namespace System {
namespace detail {

    inline void access_global_glfw_windows(const std::function<void(std::set<GLFWwindow*>&)>&);
    inline GLFWwindow* create_glfw_window(const Window::Info&);
    inline void destroy_glfw_window(GLFWwindow*);
    inline void glfw_framebuffer_size_callback(GLFWwindow*, int, int);
    inline void glfw_char_callback(GLFWwindow*, unsigned int);
    inline void glfw_keyboard_callback(GLFWwindow*, int, int, int, int);
    inline void glfw_mouse_button_callback(GLFWwindow*, int, int, int);
    inline void glfw_mouse_position_callback(GLFWwindow*, double, double);
    inline void glfw_mouse_scroll_callback(GLFWwindow*, double, double);

} // namespace detail

    /*
    * Provides high level control over a GLFWwindow.
    */
    class GLFWWindow final
        : public Window
    {
    private:
        GLFWwindow* mGlfwWindow { nullptr };

    public:
        /*
        * Constructs an instance of GLFWWindow.
        * @param [in] windowInfo This GLFWWindow's Window::Info
        */
        inline GLFWWindow(const Window::Info& windowInfo)
        {
            mGraphicsApi = windowInfo.graphicsApi;
            mGlfwWindow = detail::create_glfw_window(windowInfo);
            glfwSetWindowUserPointer(mGlfwWindow, this);
        }

        /*
        * Moves an instance of GLFWWindow.
        * @param [in] other The GLFWWindow to move from
        */
        inline GLFWWindow(GLFWWindow&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of GLFWWindow.
        */
        inline ~GLFWWindow()
        {

        }

        /*
        * Moves this instance of GLFWWindow
        * @param [in] other The GLFWWindow to move from
        * @return This GLFWWindow
        */
        GLFWWindow& operator=(GLFWWindow&& other)
        {
            if (this != &other) {
                Window::operator=(std::move(other));
                glfwSetWindowUserPointer(mGlfwWindow, this);
                mGlfwWindow = std::move(other.mGlfwWindow);
                other.mGlfwWindow = nullptr;
            }
            return *this;
        }

    public:
        /*
        * Gets this GlfwWindow's GLFWwindow.
        * @return This GlfwWindow's GLFWwindow
        */
        inline GLFWwindow* get_glfw_window() const
        {
            return mGlfwWindow;
        }

        /*
        * Gets this GLFWWindow's Resolution.
        * @return This GLFWWindow's Resolution
        */
        inline Resolution get_resolution() const override final
        {
            int width, height;
            glfwGetWindowSize(mGlfwWindow, &width, &height);
            return { width, height };
        }

        /*
        * TODO : Documentation.
        */
        inline void poll_events() override final
        {
            glfwPollEvents();
            detail::access_global_glfw_windows(
                [](std::set<GLFWwindow*>& glfwWindows)
                {
                    for (auto glfwWindow : glfwWindows) {
                        auto window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
                        window->mInput.update();
                    }
                }
            );
        }

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        * TODO : Documentation.
        */
        inline void swap() override
        {
            if (mGraphicsApi == GraphicsApi::OpenGL) {
                glfwSwapBuffers(mGlfwWindow);
            }
        }
        #endif

    private:
        friend void detail::glfw_framebuffer_size_callback(GLFWwindow*, int, int);
        friend void detail::glfw_char_callback(GLFWwindow* glfwWindow, unsigned int);
        friend void detail::glfw_keyboard_callback(GLFWwindow*, int, int, int, int);
        friend void detail::glfw_mouse_button_callback(GLFWwindow*, int, int, int);
        friend void detail::glfw_mouse_position_callback(GLFWwindow*, double, double);
        friend void detail::glfw_mouse_scroll_callback(GLFWwindow*, double, double);
    };

namespace detail {

    inline void access_global_glfw_windows(
        const std::function<void(std::set<GLFWwindow*>&)>& accessFunction
    )
    {
        static std::mutex sMutex;
        static std::set<GLFWwindow*> sGlfwWindowHandles;
        std::lock_guard<std::mutex> lock(sMutex);
        accessFunction(sGlfwWindowHandles);
    }

    inline GLFWwindow* create_glfw_window(const Window::Info& windowInfo)
    {
        GLFWwindow* glfwWindow = nullptr;
        detail::access_global_glfw_windows(
            [&](std::set<GLFWwindow*>& glfwWindows)
            {
                if (glfwWindows.empty()) {
                    glfwSetErrorCallback(detail::glfw_error_callback);
                    if (glfwInit() == GLFW_FALSE) {
                        // TODO : Get error message.
                        throw std::runtime_error("Failed to initialize GLFW : ");
                    }

                    switch (windowInfo.graphicsApi) {
                        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                        case GraphicsApi::OpenGL:
                        {
                            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowInfo.openGlContextInfo.version.major);
                            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowInfo.openGlContextInfo.version.minor);
                            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                        } break;
                        #endif

                        #if defined(DYNAMIC_STATIC_SYSTEM_VULKAN_ENABLED)
                        case GraphicsApi::Vulkan:
                        #endif
                        default:
                        {
                            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                        } break;
                    }
                }

                glfwWindowHint(GLFW_VISIBLE, windowInfo.visible);
                glfwWindowHint(GLFW_DECORATED, windowInfo.decorated);
                glfwWindowHint(GLFW_RESIZABLE, windowInfo.resizable);
                glfwWindow = glfwCreateWindow(
                    windowInfo.resolution.width,
                    windowInfo.resolution.height,
                    windowInfo.name.c_str(),
                    windowInfo.fullScreen ? glfwGetPrimaryMonitor() : nullptr,
                    /* windowInfo.parent ? windowInfo.parent->get_glfw_window() : */ nullptr
                );
                if (!glfwWindow) {
                    detail::destroy_glfw_window(glfwWindow);
                    // TODO : Get error message.
                    throw std::runtime_error("Failed to create GLFW Window : ");
                }

                #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                if (windowInfo.graphicsApi == GraphicsApi::OpenGL) {
                    glfwMakeContextCurrent(glfwWindow);
                    glfwSwapInterval(windowInfo.openGlContextInfo.vSync ? 1 : 0);
                    #if defined(DYNAMIC_STATIC_WINDOWS)
                    try {
                        initialize_glew();
                    } catch (const std::runtime_error& e) {
                        detail::destroy_glfw_window(glfwWindow);
                        throw e;
                    }
                    #endif
                }
                #endif

                glfwSetFramebufferSizeCallback(glfwWindow, detail::glfw_framebuffer_size_callback);
                glfwSetMouseButtonCallback(glfwWindow, detail::glfw_mouse_button_callback);
                glfwSetCursorPosCallback(glfwWindow, detail::glfw_mouse_position_callback);
                glfwSetScrollCallback(glfwWindow, detail::glfw_mouse_scroll_callback);
                glfwSetKeyCallback(glfwWindow, detail::glfw_keyboard_callback);
                glfwSetCharCallback(glfwWindow, detail::glfw_char_callback);
                glfwWindows.insert(glfwWindow);
            }
        );
        return glfwWindow;
    }

    inline void destroy_glfw_window(GLFWwindow* glfwWindow)
    {
        access_global_glfw_windows(
            [&](std::set<GLFWwindow*>& glfwWindows)
            {
                if (glfwWindow) {
                    glfwDestroyWindow(glfwWindow);
                }
                glfwWindows.erase(glfwWindow);
                if (glfwWindows.empty()) {
                    glfwTerminate();
                }
            }
        );
    }

    inline void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height)
    {

    }

    inline void glfw_char_callback(GLFWwindow* glfwWindow, unsigned int codepoint)
    {

    }

    inline void glfw_keyboard_callback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods)
    {

    }

    inline void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods)
    {

    }

    inline void glfw_mouse_position_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
    {

    }

    inline void glfw_mouse_scroll_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
    {

    }

} // namespace detail
} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)
