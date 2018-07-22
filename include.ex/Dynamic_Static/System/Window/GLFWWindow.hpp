
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

#include "Dynamic_Static/Core/Events.hpp"
#include "Dynamic_Static/System/Window/Window.hpp"
#include "Dynamic_Static/System/GLFW.hpp"

#include <utility>

namespace Dynamic_Static {
namespace System {

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
            mGlfwWindow = create_glfw_window(windowInfo);
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
            if (mGlfwWindow) {
                destroy_glfw_window(mGlfwWindow);
            }
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

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        * TODO : Documentation.
        */
        inline void swap() override final
        {
            if (mGraphicsApi == GraphicsApi::OpenGL) {
                glfwSwapBuffers(mGlfwWindow);
            }
        }
        #endif

        /*
        * TODO : Documentation.
        */
        static inline void poll_events()
        {
            glfwPollEvents();
            access_global_glfw_windows(
                [](std::set<GLFWwindow*>& glfwWindows)
                {
                    for (auto glfwWindow : glfwWindows) {
                        auto window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
                        window->mInput.update();
                    }
                }
            );
        }

    private:
        static inline Delegate<>& get_poll_events_delegate()
        {
            static Delegate<> sOnPollEvents;
            sOnPollEvents = poll_events;
            return sOnPollEvents;
        }

        static inline void access_global_glfw_windows(
            const std::function<void(std::set<GLFWwindow*>&)>& accessFunction
        )
        {
            static std::mutex sMutex;
            static std::set<GLFWwindow*> sGlfwWindowHandles;
            std::lock_guard<std::mutex> lock(sMutex);
            accessFunction(sGlfwWindowHandles);
        }

        static inline void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height)
        {

        }

        static inline void glfw_char_callback(GLFWwindow* glfwWindow, unsigned int codepoint)
        {

        }

        static inline void glfw_keyboard_callback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods)
        {

        }

        static inline void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods)
        {

        }

        static inline void glfw_mouse_position_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
        {

        }

        static inline void glfw_mouse_scroll_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
        {

        }

        static inline GLFWwindow* create_glfw_window(const Window::Info& windowInfo)
        {
            GLFWwindow* glfwWindow = nullptr;
            access_global_glfw_windows(
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
                        destroy_glfw_window(glfwWindow);
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
                            destroy_glfw_window(glfwWindow);
                            throw e;
                        }
                        #endif
                    }
                    #endif

                    glfwSetFramebufferSizeCallback(glfwWindow, glfw_framebuffer_size_callback);
                    glfwSetMouseButtonCallback(glfwWindow, glfw_mouse_button_callback);
                    glfwSetCursorPosCallback(glfwWindow, glfw_mouse_position_callback);
                    glfwSetScrollCallback(glfwWindow, glfw_mouse_scroll_callback);
                    glfwSetKeyCallback(glfwWindow, glfw_keyboard_callback);
                    glfwSetCharCallback(glfwWindow, glfw_char_callback);
                    glfwWindows.insert(glfwWindow);
                    get_poll_events_event() += get_poll_events_delegate();
                }
            );
            return glfwWindow;
        }

        static void destroy_glfw_window(GLFWwindow* glfwWindow)
        {
            access_global_glfw_windows(
                [&](std::set<GLFWwindow*>& glfwWindows)
                {
                    if (glfwWindow) {
                        glfwDestroyWindow(glfwWindow);
                    }
                    glfwWindows.erase(glfwWindow);
                    if (glfwWindows.empty()) {
                        get_poll_events_event() -= get_poll_events_delegate();
                        glfwTerminate();
                    }
                }
            );
        }
    };

} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)
