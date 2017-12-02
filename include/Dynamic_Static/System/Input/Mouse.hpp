
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/Core/Math.hpp"

#include <bitset>

namespace Dynamic_Static {
namespace System {

    /**
     * Provides methods for mouse queries.
     */
    class Mouse final
    {
    public:
        /**
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

    public:
        /**
         * Represents a Mouse's state at a single moment.
         */
        struct State final
        {
        public:
            static constexpr bool Up = false;
            static constexpr bool Down = true;
            using ButtonSet = std::bitset<static_cast<size_t>(Button::Count)>;

        private:
            float mScroll { };
            glm::vec2 mPosition { };
            ButtonSet mButtons;

        public:
            /**
             * Gets a value indicating whether or not a given Button is down.
             * @param [in] button The Button to check
             * @return Whether or not the given Button is down
             */
            bool operator[](Button button) const;

            /**
             * Sets a value indicating whether or not a given Button is down.
             * @param [in] button The Button to set
             * @return Whether or not the given Button is down
             */
            ButtonSet::reference operator[](Button button);

            /**
             * Gets a value indicating whether or not a given Button is down.
             * @param [in] button The Button to check
             * @return Whether or not the given Button is down
             */
            bool operator[](size_t button) const;

            /**
             * Sets a value indicating whether or not a given Button is down.
             * @param [in] button The Button to set
             * @return Whether or not the given Button is down
             */
            ButtonSet::reference operator[](size_t button);

        public:
            /**
             * Gets this Mouse::State's scroll value.
             * @return This Mouse::State's scroll value
             */
            float get_scroll() const;

            /**
             * Sets this Mouse::State's scroll value.
             * @param [in] scroll This Mouse::State's scroll value
             */
            void set_scroll(float scroll);

            /**
             * Gets this Mouse::State's position.
             * @return This Mouse::State's position
             */
            glm::vec2 get_position() const;

            /**
             * Sets this Mouse::State's position.
             * @param [in] position This Mouse::State's position
             */
            void set_position(const glm::vec2& position);

            /**
             * Resets this Mouse::State.
             */
            void reset();
        };

    private:
        State mCurrent;
        State mPrevious;

    public:
        /**
         * Gets the delta between this Mouse's current and previous scroll.
         * @return The delta between this Mouse's current and previous scroll
         */
        float get_scroll() const;

        /**
         * Gets the delta between this Mouse's current and previous position.
         * @return The delta between this Mouse's current and previous position
         */
        glm::vec2 get_delta() const;

        /**
         * Gets this Mouse's current position.
         * @return This Mouse's current position
         */
        glm::vec2 get_position() const;

        /**
         * Gets a value indicating whether or not a given Button is up.
         * @param [in] button The Button to check
         * @return Whether or not the given Button is up
         */
        bool up(Button button) const;

        /**
         * Gets a value indicating whether or not a given Button is down.
         * @param [in] button The Button to check
         * @return Whether or not the given Button is down
         */
        bool down(Button button) const;

        /**
         * Gets a value indicating whether or not a given Button has been held.
         * @param [in] button The Button to check
         * @return Whether or not the given Button has been held
         */
        bool held(Button button) const;

        /**
         * Gets a value indicating whether or not a given Button has been pressed.
         * @param [in] button The Button to check
         * @return Whether or not the given Button has been pressed
         */
        bool pressed(Button button) const;

        /**
         * Gets a value indicating whether or not a given Button has been released.
         * @param [in] button The Button to check
         * @return Whether or not the given Button has been released
         */
        bool released(Button button) const;

        /**
         * Resets this Mouse.
         */
        void reset();

    private:
        void update(const State& state);

    private:
        friend class Input;
    };

} // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace System {

    /**
     * Converts a GLFW mouse button to a Mouse::Button.
     * @param [in] glfwMouseButton The GLFW mouse button to convert to a Mouse::Button
     * @return The converted Mouse::Button
     */
    Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton);

} // namespace System
} // namespace Dynamic_Static
