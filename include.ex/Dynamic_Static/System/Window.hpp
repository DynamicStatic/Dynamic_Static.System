
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

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
