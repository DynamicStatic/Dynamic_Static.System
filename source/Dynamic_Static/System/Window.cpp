
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/System/Window.hpp"
#include "Dynamic_Static/System/GLInclude.hpp"
#include "GLFWInclude.hpp"

#include <iostream>
#include <set>

namespace Dynamic_Static {
namespace System {

    static Window& dst_window(GLFWwindow* handle);
    static GLFWwindow* glfw_handle(const void* handle);
    static GLFWwindow* create_glfw_window(const Window::Configuration& configuration);
    static void destroy_glfw_window(GLFWwindow* handle);
    void frame_buffer_size_callback(GLFWwindow* handle, int width, int height);
    void keyboard_callback(GLFWwindow* handle, int glfwKey, int scanCode, int action, int mods);
    void mouse_button_callback(GLFWwindow* handle, int glfwButton, int action, int mods);
    void mouse_position_callback(GLFWwindow* handle, double xOffset, double yOffset);
    void mouse_scroll_callback(GLFWwindow* handle, double xOffset, double yOffset);
    void glfw_error_callback(int error, const char* description);

} // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace System {

    Window::Window(const Window::Configuration& configuration)
        : mHandle { create_glfw_window(configuration) }
        , mApi { configuration.api }
    {
        glfwSetWindowUserPointer(glfw_handle(mHandle), this);
        set_cursor_mode(configuration.cursorMode);
        set_position(configuration.position);
        visible(configuration.visible);
        set_name(configuration.name);
    }

    Window::Window(Window&& other)
    {
        *this = std::move(other);
    }

    Window::~Window()
    {
        if (mHandle) {
            destroy_glfw_window(glfw_handle(mHandle));
        }
    }

    Window& Window::operator=(Window&& other)
    {
        if (this != &other) {
            Object::operator=(std::move(other));
            mHandle = std::move(other.mHandle);
            mApi = std::move(other.mApi);
            other.mHandle = nullptr;
            glfwSetWindowUserPointer(glfw_handle(mHandle), this);
        }

        return *this;
    }

    const std::string& Window::get_name() const
    {
        return Object::get_name();
    }

    void Window::set_name(const std::string& name)
    {
        if (Object::get_name() != name) {
            Object::set_name(name);
            glfwSetWindowTitle(glfw_handle(mHandle), name.c_str());
        }
    }

    void* Window::get_display()
    {
        #if defined(DYNAMIC_STATIC_LINUX)
        return glfwGetX11Display();
        #endif
        return nullptr;
    }

    void* Window::get_handle()
    {
        #if defined(DYNAMIC_STATIC_WINDOWS)
        return glfwGetWin32Window(glfw_handle(mHandle));
        #endif
        return nullptr;
    }
        
    #if defined(DYNAMIC_STATIC_LINUX)
    X11Window Window::get_x11_window()
    {
        return glfwGetX11Window(glfw_handle(mHandle));
    }
    #endif

    const Input& Window::get_input() const
    {
        return mInputManager.get_input();
    }

    std::string Window::get_clipboard() const
    {
        auto clipboard = glfwGetClipboardString(glfw_handle(mHandle));
        return clipboard ? std::string(clipboard) : std::string();
    }

    void Window::set_clipboard(const std::string& clipboard) const
    {
        glfwSetClipboardString(glfw_handle(mHandle), clipboard.c_str());
    }

    Window::CursorMode Window::get_cursor_mode() const
    {
        auto cursorMode = CursorMode::Normal;
        switch (glfwGetInputMode(glfw_handle(mHandle), GLFW_CURSOR)) {
            case GLFW_CURSOR_NORMAL: cursorMode = CursorMode::Normal; break;
            case GLFW_CURSOR_HIDDEN: cursorMode = CursorMode::Hidden; break;
            case GLFW_CURSOR_DISABLED: cursorMode = CursorMode::Disabled; break;
        }

        return cursorMode;
    }

    void Window::set_cursor_mode(CursorMode cursorMode)
    {
        auto glfwCursorMode = GLFW_CURSOR_NORMAL;
        switch (cursorMode) {
            case CursorMode::Normal: glfwCursorMode = GLFW_CURSOR_NORMAL; break;
            case CursorMode::Hidden: glfwCursorMode = GLFW_CURSOR_HIDDEN; break;
            case CursorMode::Disabled: glfwCursorMode = GLFW_CURSOR_DISABLED; break;
        }

        glfwSetInputMode(glfw_handle(mHandle), GLFW_CURSOR, glfwCursorMode);
    }

    Resolution Window::get_resolution() const
    {
        int width, height;
        glfwGetWindowSize(glfw_handle(mHandle), &width, &height);
        return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
    }

    void Window::set_resolution(const Resolution& resolution)
    {
        auto width = static_cast<int>(resolution.width);
        auto height = static_cast<int>(resolution.height);
        glfwSetWindowSize(glfw_handle(mHandle), width, height);
    }

    glm::vec2 Window::get_position() const
    {
        int x, y;
        glfwGetWindowPos(glfw_handle(mHandle), &x, &y);
        return { static_cast<float>(x), static_cast<float>(y) };
    }

    void Window::set_position(const glm::vec2& position)
    {
        auto x = dst::round_cast<int>(position.x);
        auto y = dst::round_cast<int>(position.y);
        glfwSetWindowPos(glfw_handle(mHandle), x, y);
    }

    bool Window::visible() const
    {
        return glfwGetWindowAttrib(glfw_handle(mHandle), GLFW_VISIBLE) == 1;
    }

    void Window::visible(bool visible)
    {
        if (visible) {
            glfwShowWindow(glfw_handle(mHandle));
        } else {
            glfwHideWindow(glfw_handle(mHandle));
        }
    }

    void Window::make_current()
    {
        #if DYNAMIC_STATIC_OPENGL_SUPPORTED
        if (mApi == API::OpenGL) {
            glfwMakeContextCurrent(glfw_handle(mHandle));
        }
        #endif
    }

    void Window::swap()
    {
        mInputManager.update();
        #if DYNAMIC_STATIC_OPENGL_SUPPORTED
        if (mApi == API::OpenGL) {
            glfwSwapBuffers(glfw_handle(mHandle));
        }
        #endif
    }

    void Window::update()
    {
        glfwPollEvents();
    }

    void Window::execute_on_resized() const
    {
        on_resized(*this);
    }

} // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace System {

    static std::set<GLFWwindow*> gGLFWWindowHandles;
    static API gWindowAPI { API::Unknown };

    Window& dst_window(GLFWwindow* handle)
    {
        auto dstWindow = static_cast<Window*>(glfwGetWindowUserPointer(handle));
        assert(dstWindow != nullptr);
        return *dstWindow;
    }

    GLFWwindow* glfw_handle(const void* handle)
    {
        return static_cast<GLFWwindow*>(const_cast<void*>(handle));
    }

    GLFWwindow* create_glfw_window(const Window::Configuration& configuration)
    {
        GLFWwindow* handle = nullptr;
        if (gGLFWWindowHandles.empty()) {
            glfwSetErrorCallback(glfw_error_callback);
            if (glfwInit() == GLFW_FALSE) {
                // TODO : Get error for exception...
                throw std::runtime_error("GLFW failed to initialize");
            }

            switch (configuration.api) {
                #if DYNAMIC_STATIC_OPENGL_SUPPORTED
                case API::OpenGL:
                {
                    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, configuration.apiVersion.major);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, configuration.apiVersion.minor);
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                } break;
                #endif

                #if DYNAMIC_STATIC_VULKAN_SUPPORTED
                case API::Vulkan:
                #endif
                default:
                {
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                } break;
            }
        }

        glfwWindowHint(GLFW_VISIBLE, configuration.visible);
        glfwWindowHint(GLFW_DECORATED, configuration.decorated);
        glfwWindowHint(GLFW_RESIZABLE, configuration.resizable);
        auto width = static_cast<int>(configuration.resolution.width);
        auto height = static_cast<int>(configuration.resolution.height);

        // TODO : Parent window
        // TODO : Monitor

        handle = glfwCreateWindow(width, height, configuration.name.c_str(), nullptr, nullptr);
        if (!handle) {
            destroy_glfw_window(handle);
            // TODO : Get error for exception...
            throw std::runtime_error("Failed to create Window");
        }

        #if DYNAMIC_STATIC_OPENGL_SUPPORTED
        if (configuration.api == API::OpenGL) {
            static bool sGLEWInitialized;
            if (!sGLEWInitialized) {
                glfwMakeContextCurrent(handle);
                #if defined(DYNAMIC_STATIC_WINDOWS)
                glewExperimental = true;
                auto error = glewInit();
                if (error) {
                    destroy_glfw_window(handle);
                    // TODO : Get error for exception...
                    throw std::runtime_error("Failed to initialize GLEW");
                }
                #endif

                sGLEWInitialized = true;
            }
        }
        #endif

        if (configuration.vSync) {
            glfwSwapInterval(1);
        }

        glfwSetFramebufferSizeCallback(handle, frame_buffer_size_callback);
        glfwSetMouseButtonCallback(handle, mouse_button_callback);
        glfwSetCursorPosCallback(handle, mouse_position_callback);
        glfwSetScrollCallback(handle, mouse_scroll_callback);
        glfwSetKeyCallback(handle, keyboard_callback);
        return handle;
    }

    void destroy_glfw_window(GLFWwindow* handle)
    {
        if (handle) {
            glfwDestroyWindow(handle);
        }

        gGLFWWindowHandles.erase(handle);
        if (gGLFWWindowHandles.empty()) {
            glfwTerminate();
        }
    }

    void frame_buffer_size_callback(GLFWwindow* handle, int /* width */, int /* height */)
    {
        dst_window(handle).execute_on_resized();
    }

    void keyboard_callback(GLFWwindow* handle, int glfwKey, int scanCode, int action, int /* mods */)
    {
        auto& input = dst_window(handle).mInputManager;
        auto dstKey = glfw_to_dst_key(glfwKey);
        switch (action) {
            case GLFW_PRESS:
                input.get_keyboard_state()[dstKey] = Keyboard::State::Down;
                break;

            case GLFW_RELEASE:
                input.get_keyboard_state()[dstKey] = Keyboard::State::Up;
                break;

            case GLFW_REPEAT:
                input.get_keyboard_state()[dstKey] = Keyboard::State::Down;
                break;
        }
    }

    void mouse_button_callback(GLFWwindow* handle, int glfwButton, int action, int /* mods */)
    {
        auto& input = dst_window(handle).mInputManager;
        auto dstButton = glfw_to_dst_mouse_button(glfwButton);
        switch (action) {
            case GLFW_PRESS:
                input.get_mouse_state()[dstButton] = Mouse::State::Down;
                break;

            case GLFW_RELEASE:
                input.get_mouse_state()[dstButton] = Mouse::State::Up;
                break;

            case GLFW_REPEAT:
                input.get_mouse_state()[dstButton] = Mouse::State::Down;
                break;
        }
    }

    void mouse_position_callback(GLFWwindow* handle, double xOffset, double yOffset)
    {
        dst_window(handle).mInputManager.get_mouse_state().set_position({ xOffset, yOffset });
    }

    void mouse_scroll_callback(GLFWwindow* handle, double /* xOffset */, double yOffset)
    {
        auto& input = dst_window(handle).mInputManager;
        auto scroll = input.get_mouse_state().get_scroll();
        input.get_mouse_state().set_scroll(scroll + static_cast<float>(yOffset));
    }

    void glfw_error_callback(int error, const char* description)
    {
        // TODO : Setup a logger...
        std::cerr << "== GLFW Error " + std::to_string(error) + " : " + std::string(description) << std::endl;
    }

} // namespace System
} // namespace Dynamic_Static
