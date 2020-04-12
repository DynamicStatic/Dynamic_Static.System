
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/window.hpp"

#include "GLFW/glfw3.h"
#ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#endif
#ifdef DYNAMIC_STATIC_PLATFORM_LINUX
#ifndef GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_X11
#endif
#ifndef GLFW_EXPOSE_NATIVE_GLX
#define GLFW_EXPOSE_NATIVE_GLX
#endif
#endif
#include "GLFW/glfw3native.h"

#include <iostream>
#include <stdexcept>

namespace dst {
namespace sys {

std::string& Window::get_last_glfw_error_message()
{
    thread_local std::string tlGlfwErrorMessage;
    return tlGlfwErrorMessage;
}

void Window::glfw_error_callback(int error, const char* pMessage)
{
    auto& lastErrorMessage = get_last_glfw_error_message();
    lastErrorMessage = "GLFW Error[" + std::to_string(error) + "] : ";
    lastErrorMessage += pMessage ? pMessage : "Unknown";
    std::cerr << lastErrorMessage << std::endl;
}

void Window::glfw_window_close_callback(GLFWwindow* pGlfwWindow)
{
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    pDstWindow->on_close_requested(*pDstWindow);
}

void Window::glfw_framebuffer_size_callback(GLFWwindow* pGlfwWindow, int width, int height)
{
    (void)width;
    (void)height;
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    pDstWindow->mInfo.extent.x = width;
    pDstWindow->mInfo.extent.y = height;
    pDstWindow->on_resize(*pDstWindow);
}

void Window::glfw_keyboard_callback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods)
{
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    auto dstKey = (int)glfw_to_dst_key(key);
    switch (action) {
    case GLFW_PRESS: pDstWindow->mInput.keyboard.staged[dstKey] = ButtonDown; break;
    case GLFW_RELEASE: pDstWindow->mInput.keyboard.staged[dstKey] = ButtonUp; break;
    case GLFW_REPEAT: pDstWindow->mInput.keyboard.staged[dstKey] = ButtonDown; break;
    default:break;
    }
}

void Window::glfw_char_callback(GLFWwindow* pGlfwWindow, unsigned int codepoint)
{
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    if (codepoint > 0 && codepoint < 0x10000) {
        pDstWindow->mTextStream.push_back((uint32_t)codepoint);
    }
}

void Window::glfw_mouse_position_callback(GLFWwindow* pGlfwWindow, double xOffset, double yOffset)
{
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    pDstWindow->mInput.mouse.staged.position = { xOffset, yOffset };
}

void Window::glfw_mouse_button_callback(GLFWwindow* pGlfwWindow, int button, int action, int mods)
{
    (void)mods;
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    auto dstButton = (int)glfw_to_dst_mouse_button(button);
    switch (action) {
    case GLFW_PRESS: pDstWindow->mInput.mouse.staged.buttons[dstButton] = ButtonDown; break;
    case GLFW_RELEASE: pDstWindow->mInput.mouse.staged.buttons[dstButton] = ButtonUp; break;
    case GLFW_REPEAT: pDstWindow->mInput.mouse.staged.buttons[dstButton] = ButtonDown; break;
    default:break;
    }
}

void Window::glfw_mouse_scroll_callback(GLFWwindow* pGlfwWindow, double xOffset, double yOffset)
{
    auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
    assert(pDstWindow);
    pDstWindow->mInput.mouse.staged.scroll += (float)yOffset;
}

GLFWwindow* Window::create_glfw_window(const Info& info)
{
    GLFWwindow* pGlfwWindow = nullptr;
    access_glfw_windows(
        [&](std::set<GLFWwindow*>& glfwWindows)
        {
            if (glfwWindows.empty()) {
                glfwSetErrorCallback(glfw_error_callback);
                if (glfwInit() == GLFW_FALSE) {
                    throw std::runtime_error("Failed to initialize GLFW : " + get_last_glfw_error_message());
                }
                switch (info.graphicsApi) {
                #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
                case gfx::Api::OpenGL: {
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.glContextInfo.version.major);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.glContextInfo.version.minor);
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                } break;
                #endif // DYNAMIC_STATIC_OPENGL_ENABLED
                default: {
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                } break;
                }
            }
            glfwWindowHint(GLFW_VISIBLE, 1); // (int)(info.flags & Window::Info::Flags::Visible));
            glfwWindowHint(GLFW_DECORATED, 1); // (int)(info.flags & Window::Info::Flags::Decorated));
            glfwWindowHint(GLFW_RESIZABLE, 1); // (int)(info.flags & Window::Info::Flags::Resizable));
            pGlfwWindow = glfwCreateWindow(
                info.extent.x,
                info.extent.y,
                info.pName,
                nullptr, // (int)(info.flags & Window::Info::Flags::Fullscreen) ? glfwGetPrimaryMonitor() : nullptr,
                nullptr
            );
            if (!pGlfwWindow) {
                auto errorMessage = get_last_glfw_error_message();
                if (glfwWindows.empty()) {
                    glfwTerminate();
                }
                throw std::runtime_error("Failed to create GLFW window : " + errorMessage);
            }
            #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
            if (info.graphicsApi == gfx::Api::OpenGL) {
                glfwMakeContextCurrent(pGlfwWindow);
                glfwSwapInterval(0); // (int)(info.glContextInfo.flags & gl::Context::Info::Flags::VSync));
                #ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
                if (!gl::initialize_glew()) {
                    destroy_glfw_window(pGlfwWindow);
                    throw std::runtime_error("Failed to initialize GLEW");
                }
                #endif // DYNAMIC_STATIC_PLATFORM_WINDOWS
            }
            #endif // DYNAMIC_STATIC_OPENGL_ENABLED
            glfwSetWindowCloseCallback(pGlfwWindow, glfw_window_close_callback);
            glfwSetFramebufferSizeCallback(pGlfwWindow, glfw_framebuffer_size_callback);
            glfwSetKeyCallback(pGlfwWindow, glfw_keyboard_callback);
            glfwSetCharCallback(pGlfwWindow, glfw_char_callback);
            glfwSetCursorPosCallback(pGlfwWindow, glfw_mouse_position_callback);
            glfwSetMouseButtonCallback(pGlfwWindow, glfw_mouse_button_callback);
            glfwSetScrollCallback(pGlfwWindow, glfw_mouse_scroll_callback);
            glfwWindows.insert(pGlfwWindow);
        }
    );
    return pGlfwWindow;
}

void Window::destroy_glfw_window(GLFWwindow* pGlfwWindow)
{
    access_glfw_windows(
        [&](std::set<GLFWwindow*>& glfwWindows)
        {
            if (pGlfwWindow) {
                glfwDestroyWindow(pGlfwWindow);
            }
            glfwWindows.erase(pGlfwWindow);
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
