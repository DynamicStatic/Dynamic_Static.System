
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/mouse.hpp"

namespace dst {
namespace sys {

float Mouse::scroll_delta() const
{
    return current.scroll - previous.scroll;
}

glm::vec2 Mouse::position_delta() const
{
    return current.position - previous.position;
}

bool Mouse::up(Mouse::Button button) const
{
    return current.buttons[(int)button] == ButtonUp;
}

bool Mouse::down(Mouse::Button button) const
{
    return current.buttons[(int)button] == ButtonDown;
}

bool Mouse::held(Mouse::Button button) const
{
    return previous.buttons[(int)button] == ButtonDown && current.buttons[(int)button] == ButtonDown;
}

bool Mouse::pressed(Mouse::Button button) const
{
    return previous.buttons[(int)button] == ButtonUp && current.buttons[(int)button] == ButtonDown;
}

bool Mouse::released(Mouse::Button button) const
{
    return previous.buttons[(int)button] == ButtonDown && current.buttons[(int)button] == ButtonUp;
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

void Mouse::State::reset()
{
    scroll = { };
    position = { };
    buttons.reset();
}

} // namespace sys
} // namespace dst
