
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
#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/System/Video/GLFW.hpp"
#include "Dynamic_Static/System/Video/Window.hpp"

#include <mutex>
#include <set>
#include <string>
#include <utility>

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over a GLFWwindow.
    */
    class GLFWWindow final
        : public IWindow
    {
    private:
        GLFWwindow* mGlfwWindow { nullptr };

    public:
        /*
        * Constructs an instance of GLFWWindow.
        * @param [in] windowInfo This GLFWWindow's Window::Info
        */
        inline GLFWWindow(const IWindow::Info& windowInfo)
        {
            mGraphicsApi = windowInfo.graphicsApi;
            mGlfwWindow = create_glfw_window(windowInfo);
            glfwSetWindowUserPointer(mGlfwWindow, this);
        }

        /*
        * Moves this instance of GLFWWindow.
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
        * Moves this instance of GLFWWindow.
        * @param [in] other The GLFWWindow to move from
        * @return This GLFWWindow
        */
        GLFWWindow& operator=(GLFWWindow&& other)
        {
            if (this != &other) {
                IWindow::operator=(std::move(other));
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
        * Sets this GLFWwindow's name.
        * @param [in] name This GLFWwindow's name
        */
        void set_name(dst::string_view name) override final
        {
            if (mName != name) {
                mName = name;
                glfwSetWindowTitle(mGlfwWindow, mName.c_str());
            }
        }

        /*
        * Gets this GLFWwindow's CursorMode.
        * @return This GLFWwindow's CursorMode
        */
        CursorMode get_cursor_mode() const override final
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

        /*
        * Sets this GLFWwindow's CursorMode.
        * @param [in] cursorMode This GLFWwindow's CursorMode
        */
        void set_cursor_mode(CursorMode cursorMode) override final
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

        /*
        * Gets this GLFWwindow's clipboard.
        * @return This GLFWwindow's clipboard
        */
        std::string get_clipboard() const override final
        {
            auto clipboard = glfwGetClipboardString(mGlfwWindow);
            return clipboard ? std::string(clipboard) : std::string();
        }

        /*
        * Sets this GLFWwindow's clipboard.
        * @param [in] This GLFWwindow's clipboard
        */
        void set_clipboard(dst::string_view clipboard) override final
        {
            // TODO : Setup dst::StringView to ensure null termination.
            //        See https://stackoverflow.com/a/41288372/3453616
            glfwSetClipboardString(mGlfwWindow, std::string(clipboard).c_str());
        }

        /*
        * Gets a value indicating whether or not this GLFWwindow is visible.
        * @return Whether or not this GLFWwindow is visible
        */
        bool is_visible() const override final
        {
            return glfwGetWindowAttrib(mGlfwWindow, GLFW_VISIBLE) == 1;
        }

        /*
        * Sets a value indicating whether or not this GLFWwindow is visible.
        * @param [in] isVisible Whether or not this GLFWwindow is visible
        */
        void is_visible(bool isVisible) override final
        {
            if (isVisible) {
                glfwShowWindow(mGlfwWindow);
            } else {
                glfwHideWindow(mGlfwWindow);
            }
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

        #if defined(DYNAMIC_STATIC_WINDOWS)
        /*
        * Gets this GLFWWindow's HWND.
        * @return This GLFWWindow's HWND
        * \n NOTE : This method is only available on Windows
        */
        HWND get_hwnd() const override final
        {
            return glfwGetWin32Window(mGlfwWindow);
        }
        #endif

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        * Makes this GLFWWindow's OpenGL context current.
        * \n NOTE : This method is a noop if this GLFWWindow's GraphicsApi isn't OpenGL
        * \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        */
        virtual void make_context_current() override final
        {
            if (mGraphicsApi == GraphicsApi::OpenGL) {
                glfwMakeContextCurrent(mGlfwWindow);
            }
        }

        /*
        * Swaps this GLFWwindow's front and back buffers.
        * \n NOTE : If using OpenGL this method must be called periodically to keep this GLFWwindow up to date
        * \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        */
        inline void swap() override final
        {
            if (mGraphicsApi == GraphicsApi::OpenGL) {
                glfwSwapBuffers(mGlfwWindow);
            }
        }
        #endif

        /*
        * Processes pending system events.
        * \n NOTE : This method should be called periodically to keep all GLFWWindows up to date
        * \n NOTE : This method is triggered by Window::poll_events(), one or the other should be used, not both
        */
        static inline void poll_events()
        {
            access_global_glfw_windows(
                [](std::set<GLFWwindow*>& glfwWindows)
                {
                    for (auto glfwWindow : glfwWindows) {
                        auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
                        assert(dstWindow);
                        dstWindow->mTextStream.clear();
                    }
                    glfwPollEvents();
                    for (auto glfwWindow : glfwWindows) {
                        auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
                        assert(dstWindow);
                        dstWindow->mInput.update();
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

        static inline void glfw_window_close_callback(GLFWwindow* glfwWindow)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            dstWindow->execute_on_close_callback();
        }

        static inline void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            dstWindow->execute_on_resize_callback();
        }

        static inline void glfw_char_callback(GLFWwindow* glfwWindow, unsigned int codepoint)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            if (codepoint > 0 && codepoint < 0x10000) {
                dstWindow->mTextStream.push_back(codepoint);
            }
        }

        static inline void glfw_keyboard_callback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            auto dstKey = static_cast<size_t>(glfw_to_dst_key(key));
            switch (action) {
                case GLFW_PRESS: dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_DOWN; break;
                case GLFW_RELEASE: dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_UP; break;
                case GLFW_REPEAT: dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_DOWN; break;
                default:break;
            }
        }

        static inline void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            auto dstButton = static_cast<size_t>(glfw_to_dst_mouse_button(button));
            switch (action) {
                case GLFW_PRESS: dstWindow->mInput.mouse.staged.buttons[dstButton] = DST_BUTTON_DOWN; break;
                case GLFW_RELEASE: dstWindow->mInput.mouse.staged.buttons[dstButton] = DST_BUTTON_UP; break;
                case GLFW_REPEAT: dstWindow->mInput.mouse.staged.buttons[dstButton] = DST_BUTTON_DOWN; break;
                default:break;
            }
        }

        static inline void glfw_mouse_position_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            dstWindow->mInput.mouse.staged.position = { xOffset, yOffset };
        }

        static inline void glfw_mouse_scroll_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
        {
            auto dstWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow);
            dstWindow->mInput.mouse.staged.scroll += static_cast<float>(yOffset);
        }

        static inline GLFWwindow* create_glfw_window(const IWindow::Info& windowInfo)
        {
            GLFWwindow* glfwWindow = nullptr;
            access_global_glfw_windows(
                [&](std::set<GLFWwindow*>& glfwWindows)
                {
                    if (glfwWindows.empty()) {
                        glfwSetErrorCallback(detail::glfw_error_callback);
                        if (glfwInit() == GLFW_FALSE) {
                            throw std::runtime_error("Failed to initialize GLFW : " + detail::get_last_glfw_error_message());
                        }

                        switch (windowInfo.graphicsApi) {
                            #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                            case GraphicsApi::OpenGL:
                            {
                                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowInfo.glContextInfo.version.major);
                                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowInfo.glContextInfo.version.minor);
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
                        // TODO : Handle multiple windows / gl contexts...
                        /* windowInfo.parent ? windowInfo.parent->get_glfw_window() : */ nullptr
                    );
                    if (!glfwWindow) {
                        auto errorMessage = detail::get_last_glfw_error_message();
                        destroy_glfw_window(glfwWindow);
                        throw std::runtime_error("Failed to create GLFW Window : " + errorMessage);
                    }

                    #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                    if (windowInfo.graphicsApi == GraphicsApi::OpenGL) {
                        glfwMakeContextCurrent(glfwWindow);
                        glfwSwapInterval(windowInfo.glContextInfo.vSync ? 1 : 0);
                        #if defined(DYNAMIC_STATIC_WINDOWS)
                        try {
                            gl::detail::initialize_glew();
                        } catch (const std::runtime_error& e) {
                            destroy_glfw_window(glfwWindow);
                            throw e;
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
                    get_poll_events_event() += get_poll_events_delegate();
                }
            );
            return glfwWindow;
        }

        static inline void destroy_glfw_window(GLFWwindow* glfwWindow)
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

        static inline Keyboard::Key glfw_to_dst_key(int glfwKey)
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

        static inline Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton)
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
    };

    using Window = GLFWWindow;

} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)
