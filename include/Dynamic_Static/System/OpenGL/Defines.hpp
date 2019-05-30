
/*
==========================================
    Copyright 2017-2019 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

#ifdef DYNAMIC_STATIC_WINDOWS
#pragma warning(push, 0)
#include "GL/glew.h"
#pragma warning(pop)
#endif

#include <iostream>

#define DYNAMIC_STATIC_VALIDATE_GL_CALLS
#ifdef DYNAMIC_STATIC_VALIDATE_GL_CALLS
#define dst_gl(GL_CALL)                                           \
{                                                                 \
    GL_CALL;                                                      \
    dst::sys::gl::validate_last_gl_call(dst_file_line, #GL_CALL); \
}
#else
#define dst_gl(GL_CALL) \
{                       \
    GL_CALL;            \
}
#endif

namespace dst {
namespace sys {
namespace gl {

    /*!
    Specifies configuration paramaters for an OpenGL context
    */
    struct ContextInfo final
    {
        Version version { 4, 5, 0 }; /*!< The configured OpenGL context's Version */
        bool doubleBuffer { true };  /*!< Whether or not the configured OpenGL context has double buffering enabled (hint) */
        int depthBits { 24 };        /*!< The configured OpenGL context's depth buffer bit depth (hint) */
        int stencilBits { 8 };       /*!< The configured OpenGL context's stencil buffer bit depth (hint) */
        bool vSync { true };         /*!< Whether or not the configured OpenGL context has VSync enabled (hint) */
    };

    /*!
    Logs any errors that occured during the last OpenGL call
    @param [in] message The message to print with the OpenGL error message
    @param [in] glCall The string representation of last OpenGL call
    */
    inline GLenum validate_last_gl_call(const char* message, const char* glCall)
    {
        // TODO : Set up proper logging mechanism...
        GLenum glError = glGetError();
        if (glError != GL_NO_ERROR) {
            #ifdef DYNAMIC_STATIC_WINDOWS
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

    /*!
    Gets the info log for a given OpenGL object
    @param <GetInfoLogLengthFunctionType> The type of function to use to get the info log length
    @param <GetInfoLogFunctionType> The type of function to use to get the info log
    @param [in] handle The handle to the OpenGL object to get the info log for
    @param [in] getInfoLogLength The function to use to get the info log length
    @param [in] getInfoLog The function to use to get the info log
    @return The info log for the given OpenGL object
    */
    template <
        typename GetInfoLogLengthFunctionType,
        typename GetInfoLogFunctionType
    >
    inline std::string get_info_log(
        GLuint handle,
        GetInfoLogLengthFunctionType getInfoLogLength,
        GetInfoLogFunctionType getInfoLog
    )
    {
        GLint logLength = 0;
        dst_gl(getInfoLogLength(handle, GL_INFO_LOG_LENGTH, &logLength));
        std::string log(logLength, ' ');
        dst_gl(getInfoLog(handle, (GLsizei)log.size(), nullptr, log.data()));
        return log.data();
    }

namespace detail {

    #ifdef DYNAMIC_STATIC_WINDOWS
    /*!
    Initializes OpenGL entry points
    \n NOTE : An OpenGL context must exist before calling this function
    \n NOTE : This function is only available on Windows
    */
    inline bool initialize_glew()
    {
        static bool sGlewInitialized;
        if (!sGlewInitialized) {
            glewExperimental = true;
            auto error = glewInit();
            if (!error) {
                sGlewInitialized = true;
            }
        }
        return sGlewInitialized;
    }
    #endif

} // namespace detail
} // namespace gl
} // namespace sys
namespace gl = sys::gl;
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
