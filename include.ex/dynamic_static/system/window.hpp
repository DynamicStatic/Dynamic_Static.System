
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/enum.hpp"
#include "dynamic_static/core/event.hpp"
#include "dynamic_static/core/math.hpp"
#include "dynamic_static/core/span.hpp"
#include "dynamic_static/system/defines.hpp"
#include "dynamic_static/system/input.hpp"
#ifdef DYNAMIC_STATIC_OPENGL_ENABLED
#include "dynamic_static/system/opengl/defines.hpp"
#endif

#include <mutex>
#include <set>
#include <string>
#include <vector>

struct GLFWwindow;

namespace dst {
namespace sys {

/**
Provides high level control over a system window
*/
class Window final
{
public:
    /**
    TODO : Documentation
    */
    enum class CursorMode
    {
        Visible,  // TOOD : Documentation
        Hidden,   // TOOD : Documentation
        Disabled, // TOOD : Documentation
    };

    /**
    TODO : Documentation
    */
    struct Info final
    {
        /**
        TODO : Documentation
        */
        enum class Flags
        {
            Decorated  = 1,                              //!< TODO : Documentation
            Resizable  = 1 << 1,                         //!< TODO : Documentation
            Visible    = 1 << 2,                         //!< TODO : Documentation
            Fullscreen = 1 << 3,                         //!< TODO : Documentation
            Default    = Decorated | Visible | Resizable //!< TODO : Documentation
        };

        Flags flags { Flags::Default };
        const char* pName { "Dynamic_Static" };
        glm::ivec2 position { 320, 180 };
        glm::ivec2 extent { 1280, 720 };
        CursorMode cursorMode { CursorMode::Visible };
        gfx::Api graphicsApi { gfx::Api::Undefined };
        #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
        gl::Context::Info glContextInfo { };
        #endif
    };

    /**
    Constructs an instance of Window
    @param [in] info This Window object's Window::Info
    */
    Window(const Info& info);

    /**
    Moves this instance of Window
    @param [in] other The Window to move from
    */
    Window(Window&& other) noexcept;

    /**
    Destroys this instance of Winodw
    */
    ~Window();

    /**
    Moves this instance of Window
    @param [in] other The Window to move from
    @return A reference to this Window
    */
    Window& operator=(Window&& other) noexcept;

    /**
    TODO : Documentation
    */
    Event<Window, const Window&> on_resize;

    /**
    TODO : Documentation
    */
    Event<Window, const Window&> on_close_requested;

    /**
    TODO : Documentation
    */
    const Info& info() const;

    /**
    TODO : Documentation
    */
    const Input& input() const;

    /**
    TODO : Documentation
    */
    Input& input();

    /**
    TODO : Documentation
    */
    dst::Span<const uint32_t> text_stream() const;

    #ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
    /**
    TODO : Documentation
    */
    void* hwnd() const;
    #endif // DYNAMIC_STATIC_PLATFORM_WINDOWS

    /**
    TODO : Documentation
    */
    std::string get_clipboard() const;

    /**
    TODO : Documentation
    */
    void set_clipboard(const std::string& clipboard);

    /**
    TODO : Documentation
    */
    void set_name(const std::string& name);

    /**
    TODO : Documentation
    */
    void set_cursor_mode(CursorMode cursorMode);

    #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
    /**
    TODO : Documentation
    */
    void make_context_current();

    /**
    TODO : Documentation
    */
    void swap();
    #endif // DYNAMIC_STATIC_OPENGL_ENABLED

    /**
    TODO : Documentation
    */
    static void poll_events();

private:
    static std::mutex sMutex;
    static std::set<GLFWwindow*> sGlfwWindows;
    template <typename FunctionType>
    static inline void access_glfw_windows(FunctionType function)
    {
        std::lock_guard<std::mutex> lock(sMutex);
        function(sGlfwWindows);
    }

    static std::string& get_last_glfw_error_message();
    static void glfw_error_callback(int error, const char* pMessage);
    static void glfw_window_close_callback(GLFWwindow* pGlfwWindow);
    static void glfw_framebuffer_size_callback(GLFWwindow* pGlfwWindow, int width, int height);
    static void glfw_keyboard_callback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods);
    static void glfw_char_callback(GLFWwindow* pGlfwWindow, unsigned int codepoint);
    static void glfw_mouse_position_callback(GLFWwindow* pGlfwWindow, double xOffset, double yOffset);
    static void glfw_mouse_button_callback(GLFWwindow* pGlfwWindow, int button, int action, int mods);
    static void glfw_mouse_scroll_callback(GLFWwindow* pGlfwWindow, double xOffset, double yOffset);
    static GLFWwindow* create_glfw_window(const Info& info);
    static void destroy_glfw_window(GLFWwindow* pGlfwWindow);
    static Keyboard::Key glfw_to_dst_key(int glfwKey);
    static Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton);

    Info mInfo;
    Input mInput;
    std::vector<uint32_t> mTextStream;
    std::string mName { "Dynamic_Static" };
    GLFWwindow* mGlfwWindow { nullptr };

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
};

} // namespace sys

template <>
struct EnumClassOperators<sys::Window::Info::Flags>
{
    static constexpr bool enabled { true };
};

} // namespace dst
