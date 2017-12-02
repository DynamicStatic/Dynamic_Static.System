
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Callback.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Math.hpp"
#include "Dynamic_Static/Core/Object.hpp"
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Resolution.hpp"

#if defined(DYNAMIC_STATIC_LINUX)
typedef unsigned long X11Window;
#endif

struct GLFWwindow;

namespace Dynamic_Static {
namespace System {

    /**
     * Provides high level control over a system window.
     */
    class Window final
        : public Object
    {
    public:
        /**
         * TODO : Documentation.
         */
        enum class CursorMode
        {
            Normal,   /*!< TODO : Documentation. */
            Hidden,   /*!< TODO : Documentation. */
            Disabled, /*!< TODO : Documentation. */
        };

        /**
         * Specifies configuration parameters for a Window.
         */
        class Configuration final
        {
        public:
            API api { API::Unknown };                     /*!< TODO : Documentation. */
            Version apiVersion { 0, 0, 0 };               /*!< TODO : Documentation. */
            std::string name { "Dynamic_Static" };        /*!< TODO : Documentation. */
            CursorMode cursorMode { CursorMode::Normal }; /*!< TODO : Documentation. */
            Resolution resolution { 1280, 720 };          /*!< TODO : Documentation. */
            glm::vec2 position { 320, 180 };              /*!< TODO : Documentation. */
            bool decorated { true };                      /*!< TODO : Documentation. */
            bool resizable { true };                      /*!< TODO : Documentation. */
            bool visible { true };                        /*!< TODO : Documentation. */
            bool vSync { true };                          /*!< TODO : Documentation. */
            Window* parent { nullptr };                   /*!< TODO : Documentation. */
        };

    private:
        void* mHandle { nullptr };
        API mApi { API::Unknown };
        Input::Manager mInputManager;

    public:
        /**
         * Callback executed when this Window is resized.
         * @param [in] The Window being resized
         */
        Callback<Window, const Window&> on_resized;

    public:
        /**
         * Constructs an instance of Window.
         * @param [in] configuration The new Window's Configuration (optional = default Configuration)
         */
        Window(const Configuration& configuration);

        /**
         * Moves an instance of Window.
         * @param [in] The Window to move from
         */
        Window(Window&& other);

        /**
         * Destroys an instance of Window.
         */
        ~Window();

        /**
         * Moves an instance of Window.
         * @param [in] The Window to move from
         */
        Window& operator=(Window&& other);

    public:
        /**
         * Gets this Window's name.
         * @return This Window's name
         */
        const std::string& get_name() const final override;

        /**
         * Sets this Window's name.
         * @param [in] name This Window's name
         */
        void set_name(const std::string& name) final override;
            
        /**
         * Gets this Window's OS Display.
         * \n NOTE : This value is platform specific
         * @return This Window's OS Display
         */
        void* get_display();

        /**
         * Gets this Window's OS handle.
         * \n NOTE : This value is platform specific
         * @return This Window's OS handle
         */
        void* get_handle();

        #if defined(DYNAMIC_STATIC_LINUX)
        /**
         * TODO : Documentation.
         */
        X11Window get_x11_window();
        #endif

        /**
         * Gets this Window's Input.
         * @return This Window's Input
         */
        const Input& get_input() const;

        /**
         * Gets this Window's clipboard.
         * @return This Window's clipboard
         */
        std::string get_clipboard() const;

        /**
         * Sets this Window's clipboard.
         * @param [in] clipboard This Window's clipboard
         */
        void set_clipboard(const std::string& clipboard) const;

        /**
         * Gets this Window's CursorMode.
         * @return This Window's CursorMode
         */
        CursorMode get_cursor_mode() const;

        /**
         * Sets this Window's CursorMode.
         * @param [in] cursorMode This Window's CursorMode
         */
        void set_cursor_mode(CursorMode cursorMode);

        /**
         * Gets this Window's Resolution.
         * @return This Window's Resolution
         */
        Resolution get_resolution() const;

        /**
         * Sets this Window's Resolution
         * @param [in] resolution This Window's Resolution
         */
        void set_resolution(const Resolution& resolution);

        /**
         * Gets this Window's position.
         * @return This Window's position
         */
        glm::vec2 get_position() const;

        /**
         * Sets this Window's position
         * @param [in] position This Window's position
         */
        void set_position(const glm::vec2& position);

        /**
         * Gets a value indicating whether or not this Window is visible.
         * @return Whether or not this Window is visible
         */
        bool visible() const;

        /**
         * Sets a value indicating whether or not this Window is visible.
         * @param [in] visible Whether or not this Window is visible
         */
        void visible(bool visible);

        /**
         * Makes this Window's OpenGL context current.
         * \n NOTE : This method is a noop if this Window's API is anything besides OpenGL
         */
        void make_current();

        /**
         * Swaps this Window's buffers.
         * \n NOTE : This method is a noop if this Window's API is anything besides OpenGL
         */
        void swap();

        /**
         * Updates all Window's OS queues.
         * \n NOTE : This method must be called periodically to keep Windows up to date
         */
        static void update();

    private:
        void execute_on_resized() const;
        friend GLFWwindow* create_glfw_window(const Window::Configuration&);
        friend void frame_buffer_size_callback(GLFWwindow*, int, int);
        friend void keyboard_callback(GLFWwindow*, int, int, int, int);
        friend void mouse_button_callback(GLFWwindow*, int, int, int);
        friend void mouse_position_callback(GLFWwindow*, double, double);
        friend void mouse_scroll_callback(GLFWwindow*, double, double);
        friend void glfw_error_callback(int, const char*);
    };

} // namespace System
} // namespace Dynamic_Static
