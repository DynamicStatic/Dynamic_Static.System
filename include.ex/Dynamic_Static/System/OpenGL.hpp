
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"

#include <iostream>
#include <functional>
#include <stdexcept>

#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)

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

    /*
    * Specifies configuration paramaters for an OpenGL context.
    */
    struct OpenGLContextInfo final
    {
        Version version { 4, 5, 0 }; /*!< The configured OpenGL context's Version */
        bool doubleBuffer { true };  /*!< Whether or not the configured OpenGL context has double buffering enabled (hint) */
        int depthBits { 24 };        /*!< The configured OpenGL context's depth buffer bit depth (hint) */
        int stencilBits { 8 };       /*!< The configured OpenGL context's stencil buffer bit depth (hint) */
        bool vSync { true };         /*!< Whether or not the configured OpenGL context has VSync enabled (hint) */
    };

    /*
    * TODO : Documentation.
    */
    inline GLenum validate_last_gl_call(const char* message, const char* glCall)
    {
        // TODO : Set up proper logging mechanism...
        GLenum glError = glGetError();
        if (glError != GL_NO_ERROR) {
            #if defined(DYNAMIC_STATIC_WINDOWS)
            auto errorStr = reinterpret_cast<const char*>(gluErrorString(glError));
            if (!errorStr) {
                errorStr = "Unknown";
            }
            #endif
            std::cerr
                << "OpenGL Error [" << glError << ":" << errorStr << "]\n"
                << "    " << message << "\n"
                << "    " << glCall << "\n"
                << std::endl;
        }
        return glError;
    }

    #if defined(DYNAMIC_STATIC_WINDOWS)
    /*
    * TODO : Documentation.
    */
    static void initialize_glew()
    {
        static bool sGlewInitialized;
        if (!sGlewInitialized) {
            glewExperimental = true;
            auto error = glewInit();
            if (!error) {
                sGlewInitialized = true;
            } else {
                // TODO : Error meesage.
                throw std::runtime_error("Failed to initialize GLEW : ");
            }
        }
    }
    #endif

} // namespace Dynamic_Static
} // namespace System

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
