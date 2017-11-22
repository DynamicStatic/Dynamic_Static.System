
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#if DYNAMIC_STATIC_OPENGL_SUPPORTED
    #if DYNAMIC_STATIC_WINDOWS
        #ifndef GLEW_STATIC
        #define GLEW_STATIC
        #endif
        #include "GL/glew.h"
    #elif DYNAMIC_STATIC_LINUX
        #ifndef GLFW_INCLUDE_GLCOREARB
        #define GLFW_INCLUDE_GLCOREARB
        #endif
        #ifndef GL_GLEXT_PROTOTYPES
        #define GL_GLEXT_PROTOTYPES
        #endif
        #include "GLFW/glfw3.h"
    #endif
#endif
