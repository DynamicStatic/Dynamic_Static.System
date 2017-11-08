
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#if DYNAMIC_STATIC_WINDOWS
    #ifndef GLEW_STATIC
        #define GLEW_STATIC
    #endif
    #include "GL/glew.h"
#endif
