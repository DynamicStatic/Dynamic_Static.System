
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input/Keyboard.hpp"

namespace dst {
namespace sys {

    bool Keyboard::up(Keyboard::Key key) const
    {
        return current[(int)key] == DST_KEY_UP;
    }

    bool Keyboard::down(Keyboard::Key key) const
    {
        return current[(int)key] == DST_KEY_DOWN;
    }

    bool Keyboard::held(Keyboard::Key key) const
    {
        return
            previous[(int)key] == DST_KEY_DOWN &&
            current [(int)key] == DST_KEY_DOWN;
    }

    bool Keyboard::pressed(Keyboard::Key key) const
    {
        return
            previous[(int)key] == DST_KEY_UP &&
            current [(int)key] == DST_KEY_DOWN;
    }

    bool Keyboard::released(Keyboard::Key key) const
    {
        return
            previous[(int)key] == DST_KEY_DOWN &&
            current [(int)key] == DST_KEY_UP;
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
