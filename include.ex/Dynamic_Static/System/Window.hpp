
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#if defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)
#include "Dynamic_Static/System/Window/GLFWWindow.hpp"
#endif
#if defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)
#include "Dynamic_Static/System/Window/SDLWindow.hpp"
#endif

#include "Dynamic_Static/System/Window/Window.hpp"
