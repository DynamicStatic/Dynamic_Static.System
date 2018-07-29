
/*
==========================================
    Copyright 2017-2018 Dynamic_Static
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
#include <mutex>
#include <stdexcept>

#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
#if defined(DYNAMIC_STATIC_WINDOWS)
#include "GL/glew.h"
#include "GL/wglew.h"
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

    #if defined(DYNAMIC_STATIC_WINDOWS)
    /*
    * TODO : Documentation.
    */
    static void initialize_glew()
    {
        static std::mutex sMutex;
        std::lock_guard<std::mutex> lock(sMutex);
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

    /*
    * TODO : Documentation.
    */
    template <
        typename GetIvFunctionType,
        typename GetInfoLogFunctionType
    >
    std::string get_info_log(
        GLuint handle,
        GetIvFunctionType getIv,
        GetInfoLogFunctionType getInfoLog
    )
    {
        GLint logLength = 0;
        dst_gl(getIv(handle, GL_INFO_LOG_LENGTH, &logLength));
        std::string log(logLength, ' ');
        dst_gl(getInfoLog(handle, static_cast<GLsizei>(log.size()), nullptr, log.data()));
        return log.data();
    }

    /*
    * TODO : Documentation.
    */
    std::string get_shader_info_log(GLuint shaderHandle)
    {
        return get_info_log(shaderHandle, glGetShaderiv, glGetShaderInfoLog);
    }

    /*
    * TODO : Documentation.
    */
    std::string get_program_info_log(GLuint programHandle)
    {
        return get_info_log(programHandle, glGetProgramiv, glGetProgramInfoLog);
    }

} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
