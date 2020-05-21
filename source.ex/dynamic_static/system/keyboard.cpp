
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/keyboard.hpp"

namespace dst {
namespace sys {

bool Keyboard::up(Keyboard::Key key) const
{
    return current[(int)key] == KeyUp;
}

bool Keyboard::down(Keyboard::Key key) const
{
    return current[(int)key] == KeyDown;
}

bool Keyboard::held(Keyboard::Key key) const
{
    return previous[(int)key] == KeyDown && current[(int)key] == KeyDown;
}

bool Keyboard::pressed(Keyboard::Key key) const
{
    return previous[(int)key] == KeyUp && current[(int)key] == KeyDown;
}

bool Keyboard::released(Keyboard::Key key) const
{
    return previous[(int)key] == KeyDown && current [(int)key] == KeyUp;
}

void Keyboard::update()
{
    previous = current;
    current = staged;
}

void Keyboard::reset()
{
    previous.reset();
    current.reset();
    staged.reset();
}

} // namespace sys
} // namespace dst
