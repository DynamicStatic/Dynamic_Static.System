
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

#include "dynamic_static/core/enum.hpp"
#include "dynamic_static/core/version.hpp"

#ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
#pragma warning(push, 0)
#include "GL/glew.h"
#pragma warning(pop)
#endif

#include <iostream>
#include <mutex>

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
inline GLenum validate_call(const char* message, const char* glCall)
{
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR) {
        char const* errorStr = nullptr;
        #ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
        errorStr = (const char*)gluErrorString(glError);
        #endif
        errorStr = errorStr ? errorStr : "Unknown";
        std::cerr << "OpenGL Error [" << glError << ":" << errorStr << "]" << std::endl;
        std::cerr << "    " << message << std::endl;
        std::cerr << "    " << glCall << std::endl;
        std::cerr << std::endl;
    }
    return glError;
}

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

    /*!
    TODO : Documentation
    */
    inline void stash()
    {
        dst_gl(glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&activeTexture));
        dst_gl(GL_TEXTURE0);
        dst_gl(glGetIntegerv(GL_CURRENT_PROGRAM, &program));
        dst_gl(glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture2D));
        dst_gl(glGetIntegerv(GL_SAMPLER_BINDING, &sampler));
        dst_gl(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &arrayBuffer));
        dst_gl(glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &elementArrayBuffer));
        dst_gl(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vertexArray));
        dst_gl(glGetIntegerv(GL_POLYGON_MODE, polygonMode));
        dst_gl(glGetIntegerv(GL_VIEWPORT, viewport));
        dst_gl(glGetIntegerv(GL_SCISSOR_BOX, scissor));
        dst_gl(glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&blendSrcRgb));
        dst_gl(glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&blendDstRgb));
        dst_gl(glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&blendSrcAlpha));
        dst_gl(glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&blendDstAlpha));
        dst_gl(glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&blendEquationRgb));
        dst_gl(glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&blendEquationAlpha));
        dst_gl(blendEnabled = glIsEnabled(GL_BLEND));
        dst_gl(cullFaceEnabled = glIsEnabled(GL_CULL_FACE));
        dst_gl(depthTestEnabled = glIsEnabled(GL_DEPTH_TEST));
        dst_gl(scissorTestEnabled = glIsEnabled(GL_SCISSOR_TEST));
    }

    /*!
    TODO : Documentation
    */
    inline void apply() const
    {
        dst_gl(glActiveTexture(activeTexture));
        dst_gl(glUseProgram(program));
        dst_gl(glBindTexture(GL_TEXTURE_2D, texture2D));
        dst_gl(glBindSampler(0, sampler));
        dst_gl(glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer));
        dst_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer));
        dst_gl(glBindVertexArray(vertexArray));
        dst_gl(glPolygonMode(GL_FRONT_AND_BACK, polygonMode[0]));
        dst_gl(glViewport(viewport[0], viewport[1], (GLsizei)viewport[2], (GLsizei)viewport[3]));
        dst_gl(glScissor(scissor[0], scissor[1], (GLsizei)scissor[2], (GLsizei)scissor[3]));
        dst_gl(glBlendEquationSeparate(blendEquationRgb, blendEquationAlpha));
        dst_gl(glBlendFuncSeparate(blendSrcRgb, blendDstRgb, blendSrcAlpha, blendDstAlpha));
        auto setGlBool =
        [](GLboolean glBool, GLenum glValue)
        {
            if (glBool) {
                dst_gl(glEnable(glValue));
            } else {
                dst_gl(glDisable(glValue));
            }
        };
        setGlBool(blendEnabled, GL_BLEND);
        setGlBool(cullFaceEnabled, GL_CULL_FACE);
        setGlBool(depthTestEnabled, GL_DEPTH_TEST);
        setGlBool(scissorTestEnabled, GL_SCISSOR_TEST);
        #if 0
        if (blendEnabled) {
            dst_gl(glEnable(GL_BLEND));
        } else {
            dst_gl(glDisable(GL_BLEND));
        }
        if (cullFaceEnabled) {
            dst_gl(glEnable(GL_CULL_FACE));
        } else {
            dst_gl(glDisable(GL_CULL_FACE));
        }
        if (depthTestEnabled) {
            dst_gl(glEnable(GL_DEPTH_TEST));
        } else {
            dst_gl(glDisable(GL_DEPTH_TEST));
        }
        if (scissorTestEnabled) {
            dst_gl(glEnable(GL_SCISSOR_TEST));
        } else {
            dst_gl(glDisable(GL_SCISSOR_TEST));
        }
        #endif
    }

    GLenum activeTexture { };         //!< This Context object's active texture
    GLint program { };                //!< This Context object's program
    GLint texture2D { };              //!< This Context object's texture2D
    GLint sampler { };                //!< This Context object's sampler
    GLint arrayBuffer { };            //!< This Context object's arrayBuffer
    GLint elementArrayBuffer { };     //!< This Context object's element array buffer
    GLint vertexArray { };            //!< This Context object's vertex array
    GLint polygonMode[2] { };         //!< This Context object's polygon mode
    GLint viewport[4] { };            //!< This Context object's viewport
    GLint scissor[4] { };             //!< This Context object's scissor
    GLenum blendSrcRgb { };           //!< This Context object's blend src RRGB
    GLenum blendDstRgb { };           //!< This Context object's blend dst RGB
    GLenum blendSrcAlpha { };         //!< This Context object's blend src alpha
    GLenum blendDstAlpha { };         //!< This Context object's blend dst alpha
    GLenum blendEquationRgb { };      //!< This Context object's blend equation rgb
    GLenum blendEquationAlpha { };    //!< This Context object's blend equation alpha
    GLboolean blendEnabled { };       //!< Whether or not this Context has blend enabled
    GLboolean cullFaceEnabled { };    //!< Whether or not this Context has cull face enabled
    GLboolean depthTestEnabled { };   //!< Whether or not this Context has depth test enabled
    GLboolean scissorTestEnabled { }; //!< Whether or not this Context has scissor test enabled
};

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

#ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
/**
TODO : Documentation
*/
inline bool initialize_glew()
{
    static std::mutex sMutex;
    static bool sGlewInitialized;
    std::lock_guard<std::mutex> lock(sMutex);
    if (!sGlewInitialized) {
        glewExperimental = true;
        sGlewInitialized = !glewInit();
    }
    return sGlewInitialized;
}
#endif // DYNAMIC_STATIC_PLATFORM_WINDOWS

} // namespace gl
} // namespace sys
namespace gl = sys::gl;

template <>
struct EnumClassOperators<gl::Context::Info::Flags>
{
    static constexpr bool enabled { true };
};

} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
