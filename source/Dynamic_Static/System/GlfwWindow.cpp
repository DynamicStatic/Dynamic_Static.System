
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Window.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#include "Dynamic_Static/System/OpenGL.hpp"
#endif
#include "GLFW/glfw3.h"
#ifdef DYNAMIC_STATIC_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined DYNAMIC_STATIC_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif
#include "GLFW/glfw3native.h"

namespace dst {
namespace sys {

    std::mutex Window::sGlfwWindowsMutex;
    std::set<GLFWwindow*> Window::sGlfwWindows;

    Window::Window(const Window::Info& windowInfo)
    {
        mName = windowInfo.name;
        mGraphicsApi = windowInfo.graphicsApi;
        mGlfwWindow = create_glfw_window(windowInfo);
        glfwSetWindowUserPointer(mGlfwWindow, this);
    }

    Window::Window(Window&& other)
    {
        *this = std::move(other);
    }

    Window::~Window()
    {
        if (mGlfwWindow) {
            destroy_glfw_window(mGlfwWindow);
        }
    }

    Window& Window::operator=(Window&& other)
    {
        if (this != &other) {
            mInput = std::move(other.mInput);
            mTextStream = std::move(other.mTextStream);
            mGraphicsApi = std::move(other.mGraphicsApi);
            mGlfwWindow = std::move(other.mGlfwWindow);
            glfwSetWindowUserPointer(mGlfwWindow, this);
            other.mGlfwWindow = nullptr;
        }
        return *this;
    }

    const Input& Window::get_input() const
    {
        return mInput;
    }

    dst::Span<const uint32_t> Window::get_text_stream() const
    {
        return mTextStream;
    }

    const std::string& Window::get_name() const
    {
        return mName;
    }

    void Window::set_name(dst::StringView name)
    {
        if (mName != name) {
            mName = name;
            glfwSetWindowTitle(mGlfwWindow, mName.c_str());
        }
    }

    Window::CursorMode Window::get_cursor_mode() const
    {
        auto cursorMode = CursorMode::Visible;
        switch (glfwGetInputMode(mGlfwWindow, GLFW_CURSOR)) {
            case GLFW_CURSOR_NORMAL: cursorMode = CursorMode::Visible; break;
            case GLFW_CURSOR_HIDDEN: cursorMode = CursorMode::Hidden; break;
            case GLFW_CURSOR_DISABLED: cursorMode = CursorMode::Disabled; break;
            default: break;
        }
        return cursorMode;
    }

    void Window::set_cursor_mode(Window::CursorMode cursorMode)
    {
        auto glfwCursorMode = GLFW_CURSOR_NORMAL;
        switch (cursorMode) {
            case CursorMode::Visible: glfwCursorMode = GLFW_CURSOR_NORMAL; break;
            case CursorMode::Hidden: glfwCursorMode = GLFW_CURSOR_HIDDEN; break;
            case CursorMode::Disabled: glfwCursorMode = GLFW_CURSOR_DISABLED; break;
            default: break;
        }
        glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, glfwCursorMode);
    }

    std::string Window::get_clipboard() const
    {
        auto clipboard = glfwGetClipboardString(mGlfwWindow);
        return clipboard ? std::string(clipboard) : std::string();
    }

    void Window::set_clipboard(dst::StringView clipboard)
    {
        // TODO : Setup dst::StringView to ensure null termination.
        //  See https://stackoverflow.com/a/41288372/3453616
        glfwSetClipboardString(mGlfwWindow, std::string(clipboard).c_str());
    }

    bool Window::visible() const
    {
        return glfwGetWindowAttrib(mGlfwWindow, GLFW_VISIBLE) == 1;
    }

    void Window::visible(bool visible)
    {
        if (visible) {
            glfwShowWindow(mGlfwWindow);
        } else {
            glfwHideWindow(mGlfwWindow);
        }
    }

    glm::ivec2 Window::get_resolution() const
    {
        int width, height;
        glfwGetWindowSize(mGlfwWindow, &width, &height);
        return { width, height };
    }

    HWND Window::get_hwnd() const
    {
        return glfwGetWin32Window(mGlfwWindow);
    }

    void Window::make_context_current()
    {
        if (mGraphicsApi == GraphicsApi::OpenGL) {
            glfwMakeContextCurrent(mGlfwWindow);
        }
    }

    void Window::swap()
    {
        if (mGraphicsApi == GraphicsApi::OpenGL) {
            glfwSwapBuffers(mGlfwWindow);
        }
    }

    void Window::poll_events()
    {
        access_glfw_windows(
            [](const auto& glfwWindows)
            {
                for (auto glfwWindow : glfwWindows) {
                    auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
                    assert(dstWindow);
                    dstWindow->mTextStream.clear();
                }
                glfwPollEvents();
                for (auto glfwWindow : glfwWindows) {
                    auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
                    assert(dstWindow);
                    dstWindow->mInput.update();
                }
            }
        );
    }

    std::string& Window::get_last_glfw_error_message()
    {
        thread_local std::string tlErrorMessage;
        return tlErrorMessage;
    }

    void Window::glfw_error_callback(int error, const char* description)
    {
        auto& lastErrorMessage = get_last_glfw_error_message();
        lastErrorMessage = "GLFW Error " + std::to_string(error) + " : " + std::string(description);
        // TODO : Setup logger in dst::core.
        std::cerr << lastErrorMessage << std::endl;
    }

    void Window::glfw_window_close_callback(GLFWwindow* glfwWindow)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        dstWindow->on_close(*dstWindow);
    }

    void Window::glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        dstWindow->on_resize(*dstWindow);
    }

    void Window::glfw_char_callback(GLFWwindow* glfwWindow, unsigned int codepoint)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        if (codepoint > 0 && codepoint < 0x10000) {
            dstWindow->mTextStream.push_back(codepoint);
        }
    }

    void Window::glfw_keyboard_callback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        auto dstKey = (int)glfw_to_dst_key(key);
        switch (action) {
            case GLFW_PRESS: dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_DOWN; break;
            case GLFW_RELEASE: dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_UP; break;
            case GLFW_REPEAT: dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_DOWN; break;
            default:break;
        }
    }

    void Window::glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        auto dstButton = (int)glfw_to_dst_mouse_button(button);
        switch (action) {
            case GLFW_PRESS: dstWindow->mInput.mouse.staged.buttons[dstButton] = DST_BUTTON_DOWN; break;
            case GLFW_RELEASE: dstWindow->mInput.mouse.staged.buttons[dstButton] = DST_BUTTON_UP; break;
            case GLFW_REPEAT: dstWindow->mInput.mouse.staged.buttons[dstButton] = DST_BUTTON_DOWN; break;
            default:break;
        }
    }

    void Window::glfw_mouse_position_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        dstWindow->mInput.mouse.staged.position = { xOffset, yOffset };
    }

    void Window::glfw_mouse_scroll_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
    {
        auto dstWindow = (Window*)glfwGetWindowUserPointer(glfwWindow);
        assert(dstWindow);
        dstWindow->mInput.mouse.staged.scroll += (float)yOffset;
    }

    GLFWwindow* Window::create_glfw_window(const Window::Info& windowInfo)
    {
        GLFWwindow* glfwWindow = nullptr;
        access_glfw_windows(
            [&](std::set<GLFWwindow*>& glfwWindows)
            {
                if (glfwWindows.empty()) {
                    glfwSetErrorCallback(glfw_error_callback);
                    if (glfwInit() == GLFW_FALSE) {
                        throw std::runtime_error("Failed to initialize GLFW : " + get_last_glfw_error_message());
                    }

                    switch (windowInfo.graphicsApi) {
                        #ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
                        case GraphicsApi::OpenGL:
                        {
                            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowInfo.glContextInfo.version.major);
                            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowInfo.glContextInfo.version.minor);
                            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                        } break;
                        #endif

                        #ifdef DYNAMIC_STATIC_SYSTEM_VULKAN_ENABLED
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
                    windowInfo.resolution.x,
                    windowInfo.resolution.y,
                    windowInfo.name.c_str(),
                    windowInfo.fullScreen ? glfwGetPrimaryMonitor() : nullptr,
                    // TODO : Handle multiple windows / gl contexts...
                    /* windowInfo.parent ? windowInfo.parent->get_glfw_window() : */ nullptr
                );
                if (!glfwWindow) {
                    auto errorMessage = get_last_glfw_error_message();
                    destroy_glfw_window(glfwWindow);
                    throw std::runtime_error("Failed to create GLFW Window : " + errorMessage);
                }

                #ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
                if (windowInfo.graphicsApi == GraphicsApi::OpenGL) {
                    glfwMakeContextCurrent(glfwWindow);
                    glfwSwapInterval(windowInfo.glContextInfo.vSync ? 1 : 0);
                    #ifdef DYNAMIC_STATIC_WINDOWS
                    if (!gl::detail::initialize_glew()) {
                        destroy_glfw_window(glfwWindow);
                        throw std::runtime_error("Failed to initialize GLEW");
                    }
                    #endif
                }
                #endif

                glfwSetWindowCloseCallback(glfwWindow, glfw_window_close_callback);
                glfwSetFramebufferSizeCallback(glfwWindow, glfw_framebuffer_size_callback);
                glfwSetMouseButtonCallback(glfwWindow, glfw_mouse_button_callback);
                glfwSetCursorPosCallback(glfwWindow, glfw_mouse_position_callback);
                glfwSetScrollCallback(glfwWindow, glfw_mouse_scroll_callback);
                glfwSetKeyCallback(glfwWindow, glfw_keyboard_callback);
                glfwSetCharCallback(glfwWindow, glfw_char_callback);
                glfwWindows.insert(glfwWindow);
            }
        );
        return glfwWindow;
    }

    void Window::destroy_glfw_window(GLFWwindow* glfwWindow)
    {
        access_glfw_windows(
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

    Keyboard::Key Window::glfw_to_dst_key(int glfwKey)
    {
        auto key = Keyboard::Key::Unknown;
        switch (glfwKey) {
            case GLFW_KEY_SPACE        : key = Keyboard::Key::SpaceBar;         break;
            case GLFW_KEY_APOSTROPHE   : key = Keyboard::Key::OEM_Quote;        break;
            case GLFW_KEY_COMMA        : key = Keyboard::Key::OEM_Comma;        break;
            case GLFW_KEY_MINUS        : key = Keyboard::Key::OEM_Minus;        break;
            case GLFW_KEY_PERIOD       : key = Keyboard::Key::OEM_Period;       break;
            case GLFW_KEY_SLASH        : key = Keyboard::Key::OEM_ForwardSlash; break;
            case GLFW_KEY_0            : key = Keyboard::Key::Zero;             break;
            case GLFW_KEY_1            : key = Keyboard::Key::One;              break;
            case GLFW_KEY_2            : key = Keyboard::Key::Two;              break;
            case GLFW_KEY_3            : key = Keyboard::Key::Three;            break;
            case GLFW_KEY_4            : key = Keyboard::Key::Four;             break;
            case GLFW_KEY_5            : key = Keyboard::Key::Five;             break;
            case GLFW_KEY_6            : key = Keyboard::Key::Six;              break;
            case GLFW_KEY_7            : key = Keyboard::Key::Seven;            break;
            case GLFW_KEY_8            : key = Keyboard::Key::Eight;            break;
            case GLFW_KEY_9            : key = Keyboard::Key::Nine;             break;
            case GLFW_KEY_SEMICOLON    : key = Keyboard::Key::OEM_SemiColon;    break;
            case GLFW_KEY_EQUAL        : key = Keyboard::Key::OEM_Plus;         break;
            case GLFW_KEY_A            : key = Keyboard::Key::A;                break;
            case GLFW_KEY_B            : key = Keyboard::Key::B;                break;
            case GLFW_KEY_C            : key = Keyboard::Key::C;                break;
            case GLFW_KEY_D            : key = Keyboard::Key::D;                break;
            case GLFW_KEY_E            : key = Keyboard::Key::E;                break;
            case GLFW_KEY_F            : key = Keyboard::Key::F;                break;
            case GLFW_KEY_G            : key = Keyboard::Key::G;                break;
            case GLFW_KEY_H            : key = Keyboard::Key::H;                break;
            case GLFW_KEY_I            : key = Keyboard::Key::I;                break;
            case GLFW_KEY_J            : key = Keyboard::Key::J;                break;
            case GLFW_KEY_K            : key = Keyboard::Key::K;                break;
            case GLFW_KEY_L            : key = Keyboard::Key::L;                break;
            case GLFW_KEY_M            : key = Keyboard::Key::M;                break;
            case GLFW_KEY_N            : key = Keyboard::Key::N;                break;
            case GLFW_KEY_O            : key = Keyboard::Key::O;                break;
            case GLFW_KEY_P            : key = Keyboard::Key::P;                break;
            case GLFW_KEY_Q            : key = Keyboard::Key::Q;                break;
            case GLFW_KEY_R            : key = Keyboard::Key::R;                break;
            case GLFW_KEY_S            : key = Keyboard::Key::S;                break;
            case GLFW_KEY_T            : key = Keyboard::Key::T;                break;
            case GLFW_KEY_U            : key = Keyboard::Key::U;                break;
            case GLFW_KEY_V            : key = Keyboard::Key::V;                break;
            case GLFW_KEY_W            : key = Keyboard::Key::W;                break;
            case GLFW_KEY_X            : key = Keyboard::Key::X;                break;
            case GLFW_KEY_Y            : key = Keyboard::Key::Y;                break;
            case GLFW_KEY_Z            : key = Keyboard::Key::Z;                break;
            case GLFW_KEY_LEFT_BRACKET : key = Keyboard::Key::OEM_OpenBracket;  break;
            case GLFW_KEY_BACKSLASH    : key = Keyboard::Key::OEM_BackSlash;    break;
            case GLFW_KEY_RIGHT_BRACKET: key = Keyboard::Key::OEM_CloseBracket; break;
            case GLFW_KEY_GRAVE_ACCENT : key = Keyboard::Key::OEM_Tilde;        break;
            case GLFW_KEY_WORLD_1      : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_WORLD_2      : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_ESCAPE       : key = Keyboard::Key::Escape;           break;
            case GLFW_KEY_ENTER        : key = Keyboard::Key::Enter;            break;
            case GLFW_KEY_TAB          : key = Keyboard::Key::Tab;              break;
            case GLFW_KEY_BACKSPACE    : key = Keyboard::Key::Backspace;        break;
            case GLFW_KEY_INSERT       : key = Keyboard::Key::Insert;           break;
            case GLFW_KEY_DELETE       : key = Keyboard::Key::Delete;           break;
            case GLFW_KEY_RIGHT        : key = Keyboard::Key::RightArrow;       break;
            case GLFW_KEY_LEFT         : key = Keyboard::Key::LeftArrow;        break;
            case GLFW_KEY_DOWN         : key = Keyboard::Key::DownArrow;        break;
            case GLFW_KEY_UP           : key = Keyboard::Key::UpArrow;          break;
            case GLFW_KEY_PAGE_UP      : key = Keyboard::Key::PageUp;           break;
            case GLFW_KEY_PAGE_DOWN    : key = Keyboard::Key::PageDown;         break;
            case GLFW_KEY_HOME         : key = Keyboard::Key::Home;             break;
            case GLFW_KEY_END          : key = Keyboard::Key::End;              break;
            case GLFW_KEY_CAPS_LOCK    : key = Keyboard::Key::CapsLock;         break;
            case GLFW_KEY_SCROLL_LOCK  : key = Keyboard::Key::ScrollLock;       break;
            case GLFW_KEY_NUM_LOCK     : key = Keyboard::Key::NumLock;          break;
            case GLFW_KEY_PRINT_SCREEN : key = Keyboard::Key::PrintScreen;      break;
            case GLFW_KEY_PAUSE        : key = Keyboard::Key::Pause;            break;
            case GLFW_KEY_F1           : key = Keyboard::Key::F1;               break;
            case GLFW_KEY_F2           : key = Keyboard::Key::F2;               break;
            case GLFW_KEY_F3           : key = Keyboard::Key::F3;               break;
            case GLFW_KEY_F4           : key = Keyboard::Key::F4;               break;
            case GLFW_KEY_F5           : key = Keyboard::Key::F5;               break;
            case GLFW_KEY_F6           : key = Keyboard::Key::F6;               break;
            case GLFW_KEY_F7           : key = Keyboard::Key::F7;               break;
            case GLFW_KEY_F8           : key = Keyboard::Key::F8;               break;
            case GLFW_KEY_F9           : key = Keyboard::Key::F9;               break;
            case GLFW_KEY_F10          : key = Keyboard::Key::F10;              break;
            case GLFW_KEY_F11          : key = Keyboard::Key::F11;              break;
            case GLFW_KEY_F12          : key = Keyboard::Key::F12;              break;
            case GLFW_KEY_F13          : key = Keyboard::Key::F13;              break;
            case GLFW_KEY_F14          : key = Keyboard::Key::F14;              break;
            case GLFW_KEY_F15          : key = Keyboard::Key::F15;              break;
            case GLFW_KEY_F16          : key = Keyboard::Key::F16;              break;
            case GLFW_KEY_F17          : key = Keyboard::Key::F17;              break;
            case GLFW_KEY_F18          : key = Keyboard::Key::F18;              break;
            case GLFW_KEY_F19          : key = Keyboard::Key::F19;              break;
            case GLFW_KEY_F20          : key = Keyboard::Key::F20;              break;
            case GLFW_KEY_F21          : key = Keyboard::Key::F21;              break;
            case GLFW_KEY_F22          : key = Keyboard::Key::F22;              break;
            case GLFW_KEY_F23          : key = Keyboard::Key::F23;              break;
            case GLFW_KEY_F24          : key = Keyboard::Key::F24;              break;
            case GLFW_KEY_F25          : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_KP_0         : key = Keyboard::Key::NumPad0;          break;
            case GLFW_KEY_KP_1         : key = Keyboard::Key::NumPad1;          break;
            case GLFW_KEY_KP_2         : key = Keyboard::Key::NumPad2;          break;
            case GLFW_KEY_KP_3         : key = Keyboard::Key::NumPad3;          break;
            case GLFW_KEY_KP_4         : key = Keyboard::Key::NumPad4;          break;
            case GLFW_KEY_KP_5         : key = Keyboard::Key::NumPad5;          break;
            case GLFW_KEY_KP_6         : key = Keyboard::Key::NumPad6;          break;
            case GLFW_KEY_KP_7         : key = Keyboard::Key::NumPad7;          break;
            case GLFW_KEY_KP_8         : key = Keyboard::Key::NumPad8;          break;
            case GLFW_KEY_KP_9         : key = Keyboard::Key::NumPad9;          break;
            case GLFW_KEY_KP_DECIMAL   : key = Keyboard::Key::Decimal;          break;
            case GLFW_KEY_KP_DIVIDE    : key = Keyboard::Key::Divide;           break;
            case GLFW_KEY_KP_MULTIPLY  : key = Keyboard::Key::Multiply;         break;
            case GLFW_KEY_KP_SUBTRACT  : key = Keyboard::Key::Subtract;         break;
            case GLFW_KEY_KP_ADD       : key = Keyboard::Key::Add;              break;
            case GLFW_KEY_KP_ENTER     : key = Keyboard::Key::Enter;            break;
            case GLFW_KEY_KP_EQUAL     : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_LEFT_SHIFT   : key = Keyboard::Key::LeftShift;        break;
            case GLFW_KEY_LEFT_CONTROL : key = Keyboard::Key::LeftControl;      break;
            case GLFW_KEY_LEFT_ALT     : key = Keyboard::Key::Alt;              break;
            case GLFW_KEY_LEFT_SUPER   : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_RIGHT_SHIFT  : key = Keyboard::Key::RightShift;       break;
            case GLFW_KEY_RIGHT_CONTROL: key = Keyboard::Key::RightControl;     break;
            case GLFW_KEY_RIGHT_ALT    : key = Keyboard::Key::Alt;              break;
            case GLFW_KEY_RIGHT_SUPER  : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_MENU         : key = Keyboard::Key::Unknown;          break;
            default:                     key = Keyboard::Key::Unknown;          break;
        }
        return key;
    }

    Mouse::Button Window::glfw_to_dst_mouse_button(int glfwMouseButton)
    {
        auto button = Mouse::Button::Unknown;
        switch (glfwMouseButton) {
            case GLFW_MOUSE_BUTTON_LEFT  : button = Mouse::Button::Left;    break;
            case GLFW_MOUSE_BUTTON_RIGHT : button = Mouse::Button::Right;   break;
            case GLFW_MOUSE_BUTTON_MIDDLE: button = Mouse::Button::Middle;  break;
            case GLFW_MOUSE_BUTTON_4     : button = Mouse::Button::X1;      break;
            case GLFW_MOUSE_BUTTON_5     : button = Mouse::Button::X2;      break;
            case GLFW_MOUSE_BUTTON_6     : button = Mouse::Button::Unknown; break;
            case GLFW_MOUSE_BUTTON_7     : button = Mouse::Button::Unknown; break;
            case GLFW_MOUSE_BUTTON_LAST  : button = Mouse::Button::Unknown; break;
            default: button = Mouse::Button::Unknown;
        }
        return button;
    }

} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
