
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/system/defines.hpp"

#include <bitset>

namespace dst {
namespace sys {

static constexpr bool ButtonUp { false };  // TODO : Documentation
static constexpr bool ButtonDown { true }; // TODO : Documentation

/**
Provides high level control over mouse queries
*/
struct Mouse final
{
    /**
    TODO : Documentations
    */
    enum class Button
    {
        // NOTE : The following table shows the symbolic constant names, hexadecimal
        //  values, and mouse or keyboard equivalents for the virtual key codes used by
        //  Windows.  The codes are listed in numeric order.
        //  http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

        Left         = 0x01,
        Right        = 0x02,

        #if 0
        // NOTE : This virtual key code is used by dst::sys::Keyboard
        ControlBreak = 0x03,
        #endif

        Middle       = 0x04,
        X1           = 0x05,
        X2           = 0x06,

        Unknown,
        Count,
        Any,
    };

    /**
    Gets the delta between this Mouse object's current and previous scroll
    @return The delta between this Mouse object's current and previous scroll
    */
    float scroll_delta() const;

    /**
    Gets the delta between this Mouse object's current and previous position
    @return The delta between this Mouse object's current and previous position
    */
    glm::vec2 position_delta() const;

    /**
    Gets a value indicating whether or not a given Mouse::Button is up
    @param [in] button The Mouse::Button to check
    @return Whether or not the given Mouse::Button is up
    */
    bool up(Mouse::Button button) const;

    /**
    Gets a value indicating whether or not a given Mouse::Button is down
    @param [in] button The Mouse::Button to check
    @return Whether or not the given Mouse::Button is down
    */
    bool down(Mouse::Button button) const;

    /**
    Gets a value indicating whether or not a given Mouse::Button has been held
    @param [in] button The Mouse::Button to check
    @return Whether or not the given Mouse::Button has been held
    */
    bool held(Mouse::Button button) const;

    /**
    Gets a value indicating whether or not a given Mouse::Button has been pressed
    @param [in] button The Mouse::Button to check
    @return Whether or not the given Mouse::Button has been pressed
    */
    bool pressed(Mouse::Button button) const;

    /**
    Gets a value indicating whether or not a given Mouse::Button has been released
    @param [in] button The Mouse::Button to check
    @return Whether or not the given Mouse::Button has been released
    */
    bool released(Mouse::Button button) const;

    /**
    Updates this Mouse with its staged state
        @note This method must be called periodically to keep this Mouse up to date
    */
    void update();

    /**
    Resets this Mouse
    */
    void reset();

    /**
    Represents a Mouse object's state at a single moment
    */
    struct State final
    {
        float scroll { };                                   //!< This Mouse::State object's scroll value
        glm::vec2 position { };                             //!< This Mouse::State object's position
        std::bitset<(int)Mouse::Button::Count> buttons { }; //!< This Mouse::State object's Mouse::Button state

        /**
        Resets this Mouse::State
        */
        void reset();
    };

    State previous { }; //!< This Mouse object's previous State
    State current { };  //!< This Mouse object's current State

    /**
    This Mouse object's staged State
        @note This State will be applied when update() is called
    */
    State staged { };
};

} // namespace sys
} // namespace dst
