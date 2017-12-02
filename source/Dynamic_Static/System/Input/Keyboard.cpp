
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input/Keyboard.hpp"
#include "../GLFWInclude.hpp"

namespace Dynamic_Static {
namespace System {

    Keyboard::Key glfw_to_dst_key(int glfwKey)
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

} // namespace System
} // namespace Dynamic_Static





#if 0

/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Input.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <array>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("Keyboard Key states work correctly", "[Input]")
    {
        static constexpr auto sKeyCount = static_cast<size_t>(Keyboard::Key::Count);
        std::array<bool, sKeyCount> previousKeyState;
        std::array<bool, sKeyCount> currentKeyState;
        Input::Manager inputManager;
        auto createRandomInput =
        [&](std::array<bool, sKeyCount>& keyStates)
        {
            for (size_t i = 0; i < sKeyCount; ++i) {
                auto keyState =
                    dst::Random.probability(0.5f) ?
                    Keyboard::State::Down :
                    Keyboard::State::Up;

                inputManager.get_keyboard_state()[i] = keyStates[i] = keyState;
            }

            inputManager.update();
        };

        createRandomInput(previousKeyState);
        createRandomInput(currentKeyState);

        bool success = true;
        const auto& get_input = inputManager.get_input();
        for (size_t i = 0; i < sKeyCount; ++i) {
            auto key = static_cast<Keyboard::Key>(i);
            if (key != Keyboard::Key::Unknown) {
                if (currentKeyState[i] == Keyboard::State::Up) {
                    REQUIRE(get_input.get_keyboard().up(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(get_input.get_keyboard().down(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down &&
                    previousKeyState[i] == Keyboard::State::Up) {
                    REQUIRE(get_input.get_keyboard().pressed(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down &&
                    previousKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(get_input.get_keyboard().held(key));
                }

                if (currentKeyState[i] == Keyboard::State::Up &&
                    previousKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(get_input.get_keyboard().released(key));
                }
            }
        }
    }

} // namespace Tests
} // namespace Dynamic_Static


/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Input.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <array>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("Mouse Button states work correctly", "[Input]")
    {
        static constexpr auto sButtonCount = static_cast<size_t>(Mouse::Button::Count);
        std::array<bool, sButtonCount> previousButtonState;
        std::array<bool, sButtonCount> currentButtonState;
        Input::Manager inputManager;
        auto createRandomInput =
        [&](std::array<bool, sButtonCount>& buttonStates)
        {
            for (size_t i = 0; i < sButtonCount; ++i) {
                auto buttonState =
                    dst::Random.probability(0.5f) ?
                    Mouse::State::Down :
                    Mouse::State::Up;

                inputManager.get_mouse_state()[i] = buttonStates[i] = buttonState;
            }

            inputManager.update();
        };

        createRandomInput(previousButtonState);
        createRandomInput(currentButtonState);

        bool success = true;
        const auto& get_input = inputManager.get_input();
        for (size_t i = 0; i < sButtonCount; ++i) {
            auto button = static_cast<Mouse::Button>(i);
            if (button != Mouse::Button::Unknown) {
                if (currentButtonState[i] == Mouse::State::Up) {
                    REQUIRE(get_input.get_mouse().up(button));
                }

                if (currentButtonState[i] == Mouse::State::Down) {
                    REQUIRE(get_input.get_mouse().down(button));
                }

                if (currentButtonState[i] == Mouse::State::Down &&
                    previousButtonState[i] == Mouse::State::Up) {
                    REQUIRE(get_input.get_mouse().pressed(button));
                }

                if (currentButtonState[i] == Mouse::State::Down &&
                    previousButtonState[i] == Mouse::State::Down) {
                    REQUIRE(get_input.get_mouse().held(button));
                }

                if (currentButtonState[i] == Mouse::State::Up &&
                    previousButtonState[i] == Mouse::State::Down) {
                    REQUIRE(get_input.get_mouse().released(button));
                }
            }
        }
    }

} // namespace Tests
} // namespace Dynamic_Static

#endif
