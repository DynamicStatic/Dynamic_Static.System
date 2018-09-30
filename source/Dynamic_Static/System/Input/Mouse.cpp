
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input/Mouse.hpp"

namespace dst {
namespace sys {

    void Mouse::State::reset()
    {
        scroll = { };
        position = { };
        buttons.reset();
    }

    float Mouse::get_scroll_delta() const
    {
        return current.scroll - previous.scroll;
    }

    glm::vec2 Mouse::get_position_delta() const
    {
        return current.position - previous.position;
    }

    bool Mouse::up(Mouse::Button button) const
    {
        return current.buttons[(int)button] == DST_BUTTON_UP;
    }

    bool Mouse::down(Mouse::Button button) const
    {
        return current.buttons[(int)button] == DST_BUTTON_DOWN;
    }

    bool Mouse::held(Mouse::Button button) const
    {
        return
            previous.buttons[(int)button] == DST_BUTTON_DOWN &&
            current .buttons[(int)button] == DST_BUTTON_DOWN;
    }

    bool Mouse::pressed(Mouse::Button button) const
    {
        return
            previous.buttons[(int)button] == DST_BUTTON_UP &&
            current .buttons[(int)button] == DST_BUTTON_DOWN;
    }

    bool Mouse::released(Mouse::Button button) const
    {
        return
            previous.buttons[(int)button] == DST_BUTTON_DOWN &&
            current .buttons[(int)button] == DST_BUTTON_UP;
    }

    void Mouse::update()
    {
        previous = current;
        current = staged;
    }

    void Mouse::reset()
    {
        previous.reset();
        current.reset();
        staged.reset();
    }

} // namespace sys
} // namespace dst
