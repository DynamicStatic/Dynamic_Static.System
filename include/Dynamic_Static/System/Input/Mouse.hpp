
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <bitset>

#define DST_BUTTON_UP false
#define DST_BUTTON_DOWN true

namespace dst {
namespace sys {

    /*!
    Provides high level control over mouse queries.
    */
    struct Mouse final
    {
        /*!
        Specifies Mouse buttons.
        */
        enum class Button
        {
            // NOTE : The following table shows the symbolic constant names, hexadecimal values,
            //  and mouse or keyboard equivalents for the virtual-key codes used by Windows.  The
            //  codes are listed in numeric order.
            //  http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

            Left         = 0x01,
            Right        = 0x02,

            // ControlBreak = 0x03,

            Middle       = 0x04,
            X1           = 0x05,
            X2           = 0x06,

            Unknown,
            Count,
            Any,
        };

        /*!
        Represents a Mouse's state at a single moment.
        */
        struct State final
        {
            float scroll { };                                   /*!< This Mouse::State's scroll value */
            glm::vec2 position { };                             /*!< This Mouse::State's position */
            std::bitset<(int)Mouse::Button::Count> buttons { }; /*!< This Mouse::State's Mouse::Button state */

            /*!
            Resets this Mouse::State.
            */
            void reset();
        };

        State previous { }; /*!< This Mouse's previous state */
        State current { };  /*!< This Mouse's current state */
        State staged { };   /*!< This Mouse's staging state, this state will be applied when update() is called */

        /*!
        Gets the delta between this Mouse's current and previous scroll.
        @return The delta between this Mouse's current and previous scroll
        */
        float get_scroll_delta() const;

        /*!
        Gets the delta between this Mouse's current and previous position.
        @return The delta between this Mouse's current and previous position
        */
        glm::vec2 get_position_delta() const;

        /*!
        Gets a value indicating whether or not a given Mouse::Button is up.
        @param [in] button The Mouse::Button to check
        @return Whether or not the given Mouse::Button is up
        */
        bool up(Mouse::Button button) const;

        /*!
        Gets a value indicating whether or not a given Mouse::Button is down.
        @param [in] button The Mouse::Button to check
        @return Whether or not the given Mouse::Button is down
        */
        bool down(Mouse::Button button) const;

        /*!
        Gets a value indicating whether or not a given Mouse::Button has been held.
        @param [in] button The Mouse::Button to check
        @return Whether or not the given Mouse::Button has been held
        */
        bool held(Mouse::Button button) const;

        /*!
        Gets a value indicating whether or not a given Mouse::Button has been pressed.
        @param [in] button The Mouse::Button to check
        @return Whether or not the given Mouse::Button has been pressed
        */
        bool pressed(Mouse::Button button) const;

        /*!
        Gets a value indicating whether or not a given Mouse::Button has been released.
        @param [in] button The Mouse::Button to check
        @return Whether or not the given Mouse::Button has been released
        */
        bool released(Mouse::Button button) const;

        /*!
        Updates this Mouse with its staged state.
        \n NOTE : This method must be called periodically to keep this Mouse up to date.
        */
        void update();

        /*!
        Resets this Mouse.
        */
        void reset();
    };

} // namespace sys
} // namespace dst
