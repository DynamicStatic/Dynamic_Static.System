
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/input/keyboard.hpp"
#include "dynamic_static/system/input/mouse.hpp"
#include "dynamic_static/system/defines.hpp"

namespace dst {
namespace sys {

/**
Provides high level control over input device queries
*/
struct Input final
{
    /**
    Updates this Input with its staged state
        @note This method must be called periodically to keep this Input up to date
    */
    void update();

    /**
    Resets this Input
    */
    void reset();

    /**
    Reverts this Input to its previous state
    */
    void revert();

    Keyboard keyboard { }; //!< This Input object's Keyboard
    Mouse mouse { };       //!< This Input object's Mouse

private:
    Keyboard mPreviousKeyboard;
    Mouse mPreviousMouse;
};

} // namespace sys
} // namespace dst
