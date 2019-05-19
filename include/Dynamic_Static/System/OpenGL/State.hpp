
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

#include "Dynamic_Static/System/OpenGL/Defines.hpp"

namespace dst {
namespace sys {
namespace gl {

    /*!
    Represents a snapshot of OpenGL state
    */
    struct State final
    {
        GLenum activeTexture { };          /*!< This OpenGL State's active texture */
        GLint program { };                 /*!< This OpenGL State's program */
        GLint texture2D { };               /*!< This OpenGL State's texture2D */
        GLint sampler { };                 /*!< This OpenGL State's sampler */
        GLint arrayBuffer { };             /*!< This OpenGL State's arrayBuffer */
        GLint elementArrayBuffer { };      /*!< This OpenGL State's element array buffer */
        GLint vertexArray { };             /*!< This OpenGL State's vertex array */
        GLint polygonMode[2] { };          /*!< This OpenGL State's polygon mode */
        GLint viewport[4] { };             /*!< This OpenGL State's viewport */
        GLint scissor[4] { };              /*!< This OpenGL State's scissor */
        GLenum blendSrcRgb { };            /*!< This OpenGL State's blend src RRGB */
        GLenum blendDstRgb { };            /*!< This OpenGL State's blend dst RGB */
        GLenum blendSrcAlpha { };          /*!< This OpenGL State's blend src alpha */
        GLenum blendDstAlpha { };          /*!< This OpenGL State's blend dst alpha */
        GLenum blendEquationRgb { };       /*!< This OpenGL State's blend equation rgb */
        GLenum blendEquationAlpha { };     /*!< This OpenGL State's blend equation alpha */
        GLboolean blendEnabled { };        /*!< Whether or not this OpenGL State has blend enabled */
        GLboolean cullFaceEnabled { };     /*!< Whether or not this OpenGL State has cull face enabled */
        GLboolean depthTestEnabled { };    /*!< Whether or not this OpenGL State has depth test enabled */
        GLboolean scissorTestEnabled { };  /*!< Whether or not this OpenGL State has scissor test enabled */

        /*!
        Records this State's snap shot of the current OpenGL state
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
        Sets the OpenGL state to this State's recorded snap shot
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
        }
    };

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
