
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Callback.hpp"
#include "Dynamic_Static/Core/Math.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Resolution.hpp"
#if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
#include "Dynamic_Static/System/OpenGL.hpp"
#endif

#include <vector>

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over a system window.
    */
    class Window final
        : NonCopyable
    {
    public:
        /*
        * Specifies cursor modes.
        */
        enum class CursorMode
        {
            Visible,
            Hidden,
            Disabled,
        };

        /*
        * Specifies configuration parameters for Window construction.
        */
        class Configuration final
        {
        public:
            GraphicsApi api { GraphicsApi::Unknown };       /*!< The configured Window's GraphicsApi */
            Version apiVersion { 0, 0, 0 };                 /*!< The configured Window's GraphicsApi Version */
            std::string name { "Dynamic_Static" };          /*!< The configured Window's name */
            CursorMode cursorMode { CursorMode::Visible };  /*!< The configured Window's CursorMode */
            Resolution resolution { 1280, 720 };            /*!< The configured Window's Resolution */
            glm::vec2 position { 320, 180 };                /*!< The configured Window's position */
            bool decorated { true };                        /*!< Whether or not the configured Window has decorations (hint) */
            bool resizable { true };                        /*!< Whether or not the configured Window is resizable */
            bool visible { true };                          /*!< Whether or not the configured Window is visiable */
            bool vSync { true };                            /*!< Whether or not the configured Window has VSync enabled (hint) */
            bool fullScreen { false };                      /*!< Whether or not the configured Window is full screen */
            Window* parent { nullptr };                     /*!< The configured Window's parent Window */
        };

    private:
        Configuration mConfiguration;
        void* mHandle { nullptr };
        std::vector<uint32_t> mTextStream;
        Input mInput;

    public:
        /*
        * Callback executed when this Window is resized.
        * @param [in] The Window being resized
        */
        Callback<Window, const Window&> on_resized;

    public:
        /*
        * Constructs an instance of Window.
        * @param [in] configuration This Window's Configuration (optional = default Configuration)
        */
        Window(const Configuration& configuration = { })
            : mConfiguration { configuration }
        {

        }

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        */
        Window(Window&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of Window.
        */
        ~Window()
        {
        }

        /*
        * Moves an instance of Window.
        * @param [in] other The Window to move from
        */
        Window& operator=(Window&& other);

    public:
        /*
        * Gets this Window's Configuration.
        * @return This Window's Configuration
        */
        const Configuration& get_configuration() const
        {
            mConfiguration;
        }

    private:
        #if defined(DYNAMIC_STATIC_WINDOWS) && defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        static void initialize_glew()
        {
            static bool sGlewInitialized;
            if (!sGlewInitialized) {
                sGlewInitialized = true;
                glewExperimental = true;
                auto error = glewInit();
                assert(!error);
            }
        }
        #endif
    };

    #if defined(DYNAMIC_STATIC_SDL_ENABLED)

    Window& Window::operator=(Window&& other)
    {
        if (this != &other) {

        }
        return *this;
    }

    #endif // defined(DYNAMIC_STATIC_SDL_ENABLED)

} // namespace System
} // namespace Dynamic_Static

#if 0

#include "Dynamic_Static/Core/Math.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"

#include "gsl/gsl"

#include <vector>

struct GLFWwindow;

namespace Dynamic_Static {
namespace System {

    /**
     * TODO : Documentation.
     */
    class Window
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
         * TODO : Documentation.
         */
        struct Info final
        {
            const char* name { "Dynamic_Static" };        /*!< TODO : Documentation. */
            GraphicsApi api { GraphicsApi::Unknonwn };    /*!< TODO : Documentation. */
            Version apiVersion { 0, 0, 0 };               /*!< TODO : Documentation. */
            CursorMode cursorMode { CursorMode::Normal }; /*!< TODO : Documentation. */
            glm::ivec2 resolution { 640, 480 };           /*!< TODO : Documentation. */
            glm::vec2 position { 128, 128 };              /*!< TODO : Documentation. */
            bool decorated { true };                      /*!< TODO : Documentation. */
            bool resizable { true };                      /*!< TODO : Documentation. */
            bool visible { true };                        /*!< TODO : Documentation. */
            bool vsync { true };                          /*!< TODO : Documentation. */
            bool fullScreen { false };                    /*!< TODO : Documentation. */
            Window* parent { nullptr };                   /*!< TODO : Documentation. */
        };

    private:
        Info mInfo;
        std::string mName;
        void* mHandle { nullptr };
        std::vector<uint32_t> mTextStream;
        std::string mClipBoard;
        // Input

    public:
        // Callback

    public:
        /**
         * TODO : Documentation.
         */
        Window(const Info& info);

        /**
         * TODO : Documentation.
         */
        Window(Window&& other);

        /**
         * TODO : Documentation.
         */
        ~Window();

        /**
         * TODO : Documentation.
         */
        Window& operator=(Window&& other);

    public:
        /**
         * TODO : Documentation.
         */
        const std::string& get_name() const;

        /**
         * TODO : Documentation.
         */
        void set_name(const std::string& name);

        /**
         * TODO : Documentation.
         */
        void swap_buffers() const;

        /**
         * TODO : Documentation.
         */
        static void poll_events();

    private:
        friend void glfw_key_callback(GLFWwindow* glfwWindowHandle, int glfwKey, int scanCode, int action, int mods);
        friend void glfw_framebuffer_size_callback(GLFWwindow* glfwWindowHandle, int width, int height);
        friend void glfw_mouse_button_callback(GLFWwindow* glfwWindowHandle, int glfwButton, int action, int mods);
        friend void glfw_cursor_pos_callback(GLFWwindow* glfwWindowHandle, double xOffset, double yOffset);
        friend void glfw_scroll_callback(GLFWwindow* glfwWindowHandle, double xOffset, double yOffset);
        friend void glfw_char_callback(GLFWwindow* glfwWindowHandle, unsigned int codepoint);
        friend void glfw_error_callback(int error, const char* description);
    };

} // namespace System
} // namespace Dynamic_Static

#endif
