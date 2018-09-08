
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input.hpp"

namespace Dynamic_Static {
namespace System {

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

} // namespace System
} // namespace Dynamic_Static
