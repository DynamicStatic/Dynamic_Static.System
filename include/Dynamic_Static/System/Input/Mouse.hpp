
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

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over mouse queries.
    */
    struct Mouse final
    {
        /*
        * Specifies Mouse buttons.
        */
        enum class Button
        {
            // NOTE : The following table shows the symbolic constant names, hexadecimal values,
            //        and mouse or keyboard equivalents for the virtual-key codes used by Windows.
            //        The codes are listed in numeric order.
            // http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

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

        /*
        * Represents a Mouse's state at a single moment.
        */
        struct State final
        {
            /*
            * This Mouse::State's scroll value
            */
            float scroll { };

            /*
            * This Mouse::State's position
            */
            glm::vec2 position { };

            /*
            * This Mouse::State's Mouse::Button state
            */
            std::bitset<static_cast<size_t>(Button::Count)> buttons { };

            /*
            * Resets this Mouse::State.
            */
            inline void reset()
            {
                scroll = { };
                position = { };
                buttons.reset();
            }
        };

        /*
        * This Mouse's previous state
        */
        State previous { };

        /*
        * This Mouse's current state
        */
        State current { };

        /*
        * This Mouse's staging state, this state will be applied when update() is called
        */
        State staged { };

        /*
        * Gets the delta between this Mouse's current and previous scroll.
        * @return The delta between this Mouse's current and previous scroll
        */
        inline float get_scroll_delta() const
        {
            return current.scroll - previous.scroll;
        }

        /*
        * Gets the delta between this Mouse's current and previous position.
        * @return The delta between this Mouse's current and previous position
        */
        inline glm::vec2 get_position_delta() const
        {
            return current.position - previous.position;
        }

        /*
        * Gets a value indicating whether or not a given Button is up.
        * @param [in] button The Button to check
        * @return Whether or not the given Button is up
        */
        inline bool up(Button button) const
        {
            return current.buttons[static_cast<size_t>(button)] == DST_BUTTON_UP;
        }

        /*
        * Gets a value indicating whether or not a given Button is down.
        * @param [in] button The Button to check
        * @return Whether or not the given Button is down
        */
        inline bool down(Button button) const
        {
            return current.buttons[static_cast<size_t>(button)] == DST_BUTTON_DOWN;
        }

        /*
        * Gets a value indicating whether or not a given Button has been held.
        * @param [in] button The Button to check
        * @return Whether or not the given Button has been held
        */
        inline bool held(Button button) const
        {
            return
                previous.buttons[static_cast<size_t>(button)] == DST_BUTTON_DOWN &&
                current .buttons[static_cast<size_t>(button)] == DST_BUTTON_DOWN;
        }

        /*
        * Gets a value indicating whether or not a given Button has been pressed.
        * @param [in] button The Button to check
        * @return Whether or not the given Button has been pressed
        */
        inline bool pressed(Button button) const
        {
            return
                previous.buttons[static_cast<size_t>(button)] == DST_BUTTON_UP &&
                current .buttons[static_cast<size_t>(button)] == DST_BUTTON_DOWN;
        }

        /*
        * Gets a value indicating whether or not a given Button has been released.
        * @param [in] button The Button to check
        * @return Whether or not the given Button has been released
        */
        inline bool released(Button button) const
        {
            return
                previous.buttons[static_cast<size_t>(button)] == DST_BUTTON_DOWN &&
                current .buttons[static_cast<size_t>(button)] == DST_BUTTON_UP;
        }

        /*
        * Updates this Mouse with its staged state.
        * \n NOTE : This method must be called periodically to keep this Mouse up to date.
        */
        inline void update()
        {
            previous = current;
            current = staged;
        }

        /*
        * Resets this Mouse.
        */
        inline void reset()
        {
            previous.reset();
            current.reset();
            staged.reset();
        }
    };

} // namespace System
} // namespace Dynamic_Static
