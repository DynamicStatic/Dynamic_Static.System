
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <iostream>

#if defined(DYNAMIC_STATIC_OPENGL_ENABLED)

#if defined(DYNAMIC_STATIC_WINDOWS)
    #ifndef GLEW_STATIC
    #define GLEW_STATIC 1
    #endif
    #include "GL/glew.h"
#endif

#define DYNAMIC_STATIC_VALIDATE_GL_CALLS
#if defined(DYNAMIC_STATIC_VALIDATE_GL_CALLS)
#define dst_gl(GL_CALL)                                       \
{                                                             \
    GL_CALL;                                                  \
    dst::sys::validate_last_gl_call(dst_file_line, #GL_CALL); \
}
#else
#define dst_gl(GL_CALL) \
{                       \
    GL_CALL;            \
}
#endif

namespace Dynamic_Static {
namespace System {

    inline GLenum validate_last_gl_call(const char* message, const char* glCall)
    {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            #if defined(DYNAMIC_STATIC_WINDOWS)
            auto errorStr = reinterpret_cast<const char*>(gluErrorString(error));
            if (!errorStr) {
                errorStr = "Unknown";
            }
            #endif

            std::cerr
                << "OpenGL Error [" << error << ":" << errorStr << "]\n"
                << "    " << message << "\n"
                << "    " << glCall << "\n"
                << std::endl;
        }

        return error;
    }

} // namespace Dynamic_Static
} // namespace System

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
