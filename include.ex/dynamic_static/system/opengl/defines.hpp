
/*
==========================================
    Copyright 2017-2019 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/core/version.hpp"

#ifdef DYNAMIC_STATIC_WINDOWS
#pragma warning(push, 0)
#include "GL/glew.h"
#pragma warning(pop)
#endif

#define DYNAMIC_STATIC_VALIDATE_GL_CALLS
#ifdef DYNAMIC_STATIC_VALIDATE_GL_CALLS
#define dst_gl(GL_CALL)                                   \
{                                                         \
    GL_CALL;                                              \
    dst::sys::gl::validate_call(dst_file_line, #GL_CALL); \
}
#else
#define dst_gl(GL_CALL) { GL_CALL; }
#endif

namespace dst {
namespace sys {
namespace gl {

/**
TODO : Documentation
*/
struct Context final
{
    /**
    TODO : Documentation
    */
    struct Info final
    {
        /**
        TODO : Documentation
        */
        enum class Flags
        {
            DoubleBuffer = 1,                   //!< TODO : Documentation
            VSync        = 1 << 1,              //!< TODO : Documentation
            Default      = DoubleBuffer | VSync //!< TODO : Documentation
        };

        Flags flags { Flags::Default }; //!< TODO : Documentation
        Version version { 4, 5, 0 };    //!< TODO : Documentation
        int depthBits { 24 };           //!< TODO : Documentation
        int stencilBits { 8 };          //!< TODO : Documentation
    };
};

/**
TODO : Documentation
*/
inline GLenum validate_call(const char* message, const char* glCall)
{
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR) {
        #if 0
        char const* errorStr = nullptr;
        #ifdef DYNAMIC_STATIC_WINDOWS
        auto errorStr = (const char*)gluErrorString(glError);
        #endif // DYNAMIC_STATIC_WINDOWS
        errorStr = errorStr ? errorStr : "Unknown";
        std::cerr
            << "OpenGL Error [" << glError << ":" << errorStr << "]" << std::endl
            << "    " << message << std::endl
            << "    " << glCall << std::endl
            << std::endl;
        #endif
    }
    return glError;
}

/**
TODO : Documentation
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
    GLint infoLogLength = 0;
    dst_gl(getInfoLogLength(handle, GL_INFO_LOG_LENGTH, &infoLogLength));
    std::string infoLog(infoLogLength, ' ');
    dst_gl(getInfoLog(handle, (GLsizei)infoLog.size(), nullptr, infoLog.data()));
    return infoLog;
}

} // namespace gl
} // namespace sys
namespace gl = sys::gl;
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
