
/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/time.hpp"
#include "dynamic_static/system/defines.hpp"
#include "dynamic_static/system/window.hpp"

#include "imgui.h"

namespace dst {
namespace sys {

/**
TODO : Documentation
*/
class Gui
{
public:
    /**
    Constructs an instance of Gui
    */
    Gui();

    /**
    Destroys this instance of Gui
    */
    virtual ~Gui() = 0;

    /**
    TODO : Documentation
    */
    virtual void begin_frame(const Clock& clock, Window& window);

    /**
    TODO : Documentation
    */
    virtual void end_frame();

    /**
    TODO : Documentation
    */
    virtual void draw() = 0;

private:
    static const char* get_clipboard(void* pUserData);
    static void set_clipboard(void* pUserData, const char* pClipboard);
};

} // namespace sys
} // namespace dst
