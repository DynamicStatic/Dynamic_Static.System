
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)

#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
#include "Dynamic_Static/System/Video/OpenGL.hpp"
#endif

#include "GLFW/glfw3.h"
#if defined(DYNAMIC_STATIC_WINDOWS)
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(DYNAMIC_STATIC_LINUX)
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
#endif
#include "GLFW/glfw3native.h"

#endif // defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)
