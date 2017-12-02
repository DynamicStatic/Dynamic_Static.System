
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input/Keyboard.hpp"
#include "Dynamic_Static/System/Input/Mouse.hpp"

namespace Dynamic_Static {
namespace System {

    /**
     * Provides methods for input device queries.
     */
    struct Input final
    {
        /**
         * This Input's Keyboard.
         */
        Keyboard keyboard { };

        /**
         * This Input's Mouse.
         */
        Mouse mouse { };

        /**
         * Updates this Input.
         * \n NOTE : This method must be called periodically to keep this Input up to date.
         */
        inline void update()
        {
            keyboard.update();
            mouse.update();
        }

        /**
         * Resets this Input.
         */
        inline void reset()
        {
            keyboard.reset();
            mouse.reset();
        }
    };

} // namespace System
} // namespace Dynamic_Static
