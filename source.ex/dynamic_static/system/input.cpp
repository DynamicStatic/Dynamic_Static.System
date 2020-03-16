
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/input.hpp"

namespace dst {
namespace sys {

void Input::update()
{
    keyboard.update();
    mouse.update();
}

void Input::reset()
{
    keyboard.reset();
    mouse.reset();
}

} // namespace sys
} // namespace dst
