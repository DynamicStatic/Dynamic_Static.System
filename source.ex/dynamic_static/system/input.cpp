
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/input.hpp"

#include <utility>

namespace dst {
namespace sys {

void Input::update()
{
    mPreviousKeyboard = keyboard;
    keyboard.update();
    mPreviousMouse = mouse;
    mouse.update();
}

void Input::reset()
{
    mPreviousKeyboard.reset();
    keyboard.reset();
    mPreviousMouse.reset();
    mouse.reset();
}

void Input::revert()
{
    std::swap(keyboard, mPreviousKeyboard);
    std::swap(mouse, mPreviousMouse);
}

} // namespace sys
} // namespace dst
