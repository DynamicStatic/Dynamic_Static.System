
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input/Mouse.hpp"

namespace Dynamic_Static {
namespace System {

    bool Mouse::State::operator[](Button button) const
    {
        return mButtons[static_cast<size_t>(button)];
    }

    Mouse::State::ButtonSet::reference Mouse::State::operator[](Button button)
    {
        return mButtons[static_cast<size_t>(button)];
    }

    bool Mouse::State::operator[](size_t button) const
    {
        return mButtons[button];
    }

    Mouse::State::ButtonSet::reference Mouse::State::operator[](size_t button)
    {
        return mButtons[button];
    }

    double Mouse::State::scroll() const
    {
        return mScroll;
    }

    void Mouse::State::scroll(double scroll)
    {
        mScroll = scroll;
    }

    const Vector2& Mouse::State::position() const
    {
        return mPosition;
    }

    void Mouse::State::position(const Vector2& position)
    {
        mPosition = position;
    }

    void Mouse::State::reset()
    {

        mButtons.reset();
    }

} // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace System {

    double Mouse::scroll() const
    {
        return mCurrent.scroll() - mPrevious.scroll();
    }

    Vector2 Mouse::delta() const
    {
        return mCurrent.position() - mPrevious.position();
    }

    Vector2 Mouse::position() const
    {
        return mCurrent.position();
    }

    bool Mouse::up(Button button) const
    {
        return mCurrent[button] == Mouse::State::Up;
    }

    bool Mouse::down(Button button) const
    {
        return mCurrent[button] == Mouse::State::Down;
    }

    bool Mouse::held(Button button) const
    {
        return
            mCurrent[button] == Mouse::State::Down &&
            mPrevious[button] == Mouse::State::Down;
    }

    bool Mouse::pressed(Button button) const
    {
        return
            mCurrent[button] == Mouse::State::Down &&
            mPrevious[button] == Mouse::State::Up;
    }

    bool Mouse::released(Button button) const
    {
        return
            mCurrent[button] == Mouse::State::Up &&
            mPrevious[button] == Mouse::State::Down;
    }

    void Mouse::reset()
    {
        mCurrent.reset();
        mCurrent.scroll(0);
        mCurrent.position(Vector2::Zero);
        mPrevious = mCurrent;
    }

    void Mouse::update(const State& state)
    {
        mPrevious = mCurrent;
        mCurrent = state;
    }

} // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace System {

    Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton)
    {
        auto button = Mouse::Button::Unknown;
            switch (glfwMouseButton) {
                case /* GLFW_MOUSE_BUTTON_LEFT   */ 0: button = Mouse::Button::Left; break;
                case /* GLFW_MOUSE_BUTTON_RIGHT  */ 1: button = Mouse::Button::Right; break;
                case /* GLFW_MOUSE_BUTTON_MIDDLE */ 2: button = Mouse::Button::Middle; break;
                // case /* GLFW_MOUSE_BUTTON_4      */ 3: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_5      */ 4: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_6      */ 5: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_7      */ 6: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_LAST   */ 7: button = Mouse::Button::Unknown; break;
                default: button = Mouse::Button::Unknown;
            }

        return button;
    }

} // namespace System
} // namespace Dynamic_Static
