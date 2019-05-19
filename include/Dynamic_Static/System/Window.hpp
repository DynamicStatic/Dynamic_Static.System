
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#include "Dynamic_Static/System/OpenGL/Defines.hpp"
#endif

#include <mutex>
#include <set>
#include <string>
#include <vector>

#ifdef DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
struct GLFWwindow;
#endif

namespace dst {
namespace sys {

    /*!
    Provides high level control over a system window.
    */
    class Window
        : NonCopyable
    {
    public:
        /*!
        Specifies cursor modes.
        */
        enum class CursorMode
        {
            Visible,
            Hidden,
            Disabled,
        };

        /*!
        Configuration parameters for Window construction.
        */
        class Info final
        {
        public:
            GraphicsApi graphicsApi { GraphicsApi::Unknown }; /*!< The configured Window's GraphicsApi */
            std::string name { "Dynamic_Static" };            /*!< The configured Window's name */
            CursorMode cursorMode { CursorMode::Visible };    /*!< The configured Window's CursorMode */
            glm::ivec2 resolution { 1280, 720 };              /*!< The configured Window's resolution */
            glm::vec2 position { 320, 180 };                  /*!< The configured Window's position */
            bool decorated { true };                          /*!< Whether or not the configured Window has decorations (hint) */
            bool resizable { true };                          /*!< Whether or not the configured Window is resizable */
            bool visible { true };                            /*!< Whether or not the configured Window is visiable */
            bool fullScreen { false };                        /*!< Whether or not the configured Window is full screen */

            #ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
            /*!
            The configured Window's OpenGL context info
            \n NOTE : This member is ignored if this Info's graphicsApi member isn't set to OpenGL
            \n NOTE : This member is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
            */
            gl::ContextInfo glContextInfo { };
            #endif
        };

    public:
        /*!
        Callback executed when this Window is resized.
        @param [in] The Window being resized
        */
        Callback<Window, const Window&> on_resize;

        /*!
        Callback executed when this Window is closed.
        @param [in] The Window being closed
        */
        Callback<Window, const Window&> on_close;

    protected:
        Input mInput;
        std::vector<uint32_t> mTextStream;
        std::string mName { "Dynamic_Static" };
        GraphicsApi mGraphicsApi { GraphicsApi::Unknown };
        #ifdef DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
        GLFWwindow* mGlfwWindow { nullptr };
        #endif

    public:
        /*!
        Constructs an instance of Window.
        @param [in] windowInfo This Window's Window::Info.
        */
        Window(const Window::Info& windowInfo);

        /*!
        Moves this instance of Window.
        @param [in] other The Window to move from
        */
        Window(Window&& other);

        /*!
        Destroys this instance of Winodw.
        */
        ~Window();

        /*!
        Moves this instance of Window.
        @param [in] other The Window to move from
        @return This Window
        */
        Window& operator=(Window&& other);

    public:
        /*!
        Gets this Window's Input.
        @return This Window's Input
        */
        const Input& get_input() const;

        /*!
        Gets this Window's text stream.
        @return This Window's text stream
        */
        dst::Span<const uint32_t> get_text_stream() const;

        /*!
        Gets this Window's name.
        @return This Window's name
        */
        const std::string& get_name() const;

        /*!
        Sets this Window's name.
        @param [in] name This Window's name
        */
        void set_name(dst::StringView name);

        /*!
        Gets this Window's Window::CursorMode.
        @return This Window's Window::CursorMode
        */
        Window::CursorMode get_cursor_mode() const;

        /*!
        Sets this Window's Window::CursorMode.
        @param [in] cursorMode This Window's Window::CursorMode
        */
        void set_cursor_mode(Window::CursorMode cursorMode);

        /*!
        Gets this Window's clipboard.
        @return This Window's clipboard
        */
        std::string get_clipboard() const;

        /*!
        Sets this Window's clipboard.
        @param [in] This Window's clipboard
        */
        void set_clipboard(dst::StringView clipboard);

        /*!
        Gets a value indicating whether or not this Window is visible.
        @return Whether or not this Window is visible
        */
        bool visible() const;

        /*!
        Sets a value indicating whether or not this Window is visible.
        @param [in] isVisible Whether or not this Window is visible
        */
        void visible(bool visible);

        /*!
        Gets this Window's resolution.
        @return This Window's resolution
        */
        glm::ivec2 get_resolution() const;

        #ifdef DYNAMIC_STATIC_WINDOWS
        /*!
        Gets this Window's HWND.
        @return This Window's HWND
        \n NOTE : This method is only available on Windows
        */
        HWND get_hwnd() const;
        #endif

        #ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        /*!
        Makes this Window's OpenGL context current.
        \n NOTE : This method is a noop if this Window's GraphicsApi isn't OpenGL
        \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        */
        void make_context_current();

        /*!
        Swaps this Window's front and back buffers.
        \n NOTE : If using OpenGL this method must be called periodically to keep this Window up to date
        \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        */
        void swap();
        #endif

        /*!
        Processes pending system events.
        \n NOTE : This method should be called periodically to keep all Windows up to date
        */
        static void poll_events();

    private:
        #ifdef DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
        static std::mutex sGlfwWindowsMutex;
        static std::set<GLFWwindow*> sGlfwWindows;
        template <typename AccessFunctionType>
        static inline void access_glfw_windows(AccessFunctionType accessFunction)
        {
            std::lock_guard<std::mutex> lock(sGlfwWindowsMutex);
            accessFunction(sGlfwWindows);
        }
        static std::string& get_last_glfw_error_message();
        static void glfw_error_callback(int error, const char* description);
        static void glfw_window_close_callback(GLFWwindow* glfwWindow);
        static void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
        static void glfw_char_callback(GLFWwindow* glfwWindow, unsigned int codepoint);
        static void glfw_keyboard_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
        static void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods);
        static void glfw_mouse_position_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset);
        static void glfw_mouse_scroll_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset);
        static GLFWwindow* create_glfw_window(const Window::Info& windowInfo);
        static void destroy_glfw_window(GLFWwindow* glfwWindow);
        static Keyboard::Key glfw_to_dst_key(int glfwKey);
        static Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton);
        #endif
    };

} // namespace sys
} // namespace dst
