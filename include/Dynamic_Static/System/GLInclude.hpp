
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <iostream>
#include <string>

// TODO : Move int dst::Core...
#define dst_stringify(LINE) #LINE
#define dst_expand(LINE) dst_stringify(LINE)
#define dst_file_line (__FILE__ " @line " dst_expand(__LINE__))

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

#define DYNAMIC_STATIC_VALIDATE_GL_CALLS
#if defined(DYNAMIC_STATIC_VALIDATE_GL_CALLS)
#define dst_gl(glCall)                                       \
{                                                            \
    glCall;                                                  \
    dst::sys::validate_last_gl_call(dst_file_line, #glCall); \
}
#else
#define dst_gl(glCall) \
{                      \
    glCall;            \
}
#endif

namespace Dynamic_Static {
namespace System {

    inline GLenum validate_last_gl_call(const char* message, const char* glCall)
    {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            #if DYNAMIC_STATIC_WINDOWS
            auto errorStr = reinterpret_cast<const char*>(gluErrorString(error));
            if (!errorStr) {
                errorStr = "Unknown";
            }
            #else
            auto errorStr = "TODO : GL Error String";
            #endif

            std::cerr
                << "OpenGL Error [" << error << ":" << errorStr << "]" << std::endl
                << "    " << message << std::endl
                << "    " << glCall << std::endl
                << std::endl;
        }

        return error;
    }

} // namespace System
} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_OPENGL_SUPPORTED
