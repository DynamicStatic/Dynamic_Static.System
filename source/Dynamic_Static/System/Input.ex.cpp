#if 0
/*
==========================================
  Copyright (c) 2011-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input.hpp"

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
#endif