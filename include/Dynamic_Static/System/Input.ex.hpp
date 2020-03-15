#if 0
/*
==========================================
  Copyright (c) 2011-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Input/Keyboard.hpp"
#include "Dynamic_Static/System/Input/Mouse.hpp"
#include "Dynamic_Static/System/Defines.hpp"

namespace dst {
namespace sys {

    /*!
    Provides high level control over input device queries.
    */
    struct Input final
    {
        Keyboard keyboard { };  /*!< This Input's Keyboard */
        Mouse mouse { };        /*!< This Input's Mouse */

        /*!
        Updates this Input.
        \n NOTE : This method must be called periodically to keep this Input up to date.
        */
        void update();

        /*!
        Resets this Input.
        */
        void reset();
    };

} // namespace sys
} // namespace dst
#endif