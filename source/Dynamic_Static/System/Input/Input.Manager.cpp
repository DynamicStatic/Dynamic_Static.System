
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

    Input& Input::Manager::get_input()
    {
        return mInput;
    }

    const Input& Input::Manager::get_input() const
    {
        return mInput;
    }

    Mouse::State& Input::Manager::get_mouse_state()
    {
        return mMouseState;
    }

    const Mouse::State& Input::Manager::get_mouse_state() const
    {
        return mMouseState;
    }

    Keyboard::State& Input::Manager::get_keyboard_state()
    {
        return mKeyboardState;
    }

    const Keyboard::State& Input::Manager::get_keyboard_state() const
    {
        return mKeyboardState;
    }

    void Input::Manager::update()
    {
        mInput.update(mMouseState, mKeyboardState);
    }

    void Input::Manager::reset()
    {
        mInput.reset();
        mMouseState.reset();
        mKeyboardState.reset();
    }

} // namespace System
} // namespace Dynamic_Static
