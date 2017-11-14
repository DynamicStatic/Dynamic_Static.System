
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input.hpp"

namespace Dynamic_Static {
namespace System {

    Mouse& Input::mouse()
    {
        return mMouse;
    }

    const Mouse& Input::mouse() const
    {
        return mMouse;
    }

    Keyboard& Input::keyboard()
    {
        return mKeyboard;
    }

    const Keyboard& Input::keyboard() const
    {
        return mKeyboard;
    }

    void Input::reset()
    {
        mMouse.reset();
        mKeyboard.reset();
    }

    void Input::update(
        const Mouse::State& mouseState,
        const Keyboard::State& keyboardState
    )
    {
        mMouse.update(mouseState);
        mKeyboard.update(keyboardState);
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

                inputManager.keyboard_state()[i] = keyStates[i] = keyState;
            }

            inputManager.update();
        };

        createRandomInput(previousKeyState);
        createRandomInput(currentKeyState);

        bool success = true;
        const auto& input = inputManager.input();
        for (size_t i = 0; i < sKeyCount; ++i) {
            auto key = static_cast<Keyboard::Key>(i);
            if (key != Keyboard::Key::Unknown) {
                if (currentKeyState[i] == Keyboard::State::Up) {
                    REQUIRE(input.keyboard().up(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(input.keyboard().down(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down &&
                    previousKeyState[i] == Keyboard::State::Up) {
                    REQUIRE(input.keyboard().pressed(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down &&
                    previousKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(input.keyboard().held(key));
                }

                if (currentKeyState[i] == Keyboard::State::Up &&
                    previousKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(input.keyboard().released(key));
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

                inputManager.mouse_state()[i] = buttonStates[i] = buttonState;
            }

            inputManager.update();
        };

        createRandomInput(previousButtonState);
        createRandomInput(currentButtonState);

        bool success = true;
        const auto& input = inputManager.input();
        for (size_t i = 0; i < sButtonCount; ++i) {
            auto button = static_cast<Mouse::Button>(i);
            if (button != Mouse::Button::Unknown) {
                if (currentButtonState[i] == Mouse::State::Up) {
                    REQUIRE(input.mouse().up(button));
                }

                if (currentButtonState[i] == Mouse::State::Down) {
                    REQUIRE(input.mouse().down(button));
                }

                if (currentButtonState[i] == Mouse::State::Down &&
                    previousButtonState[i] == Mouse::State::Up) {
                    REQUIRE(input.mouse().pressed(button));
                }

                if (currentButtonState[i] == Mouse::State::Down &&
                    previousButtonState[i] == Mouse::State::Down) {
                    REQUIRE(input.mouse().held(button));
                }

                if (currentButtonState[i] == Mouse::State::Up &&
                    previousButtonState[i] == Mouse::State::Down) {
                    REQUIRE(input.mouse().released(button));
                }
            }
        }
    }

} // namespace Tests
} // namespace Dynamic_Static


#endif