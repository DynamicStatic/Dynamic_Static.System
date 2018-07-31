
/*
==========================================
    Copyright 2017-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)

#include "Dynamic_Static/System/OpenGL/Defines.hpp"

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*
    * Represents a snapshot of OpenGL state.
    */
    struct State final
    {
        GLenum activeTexture { };          /*!< TODO : Documentation */
        GLint program { };                 /*!< TODO : Documentation */
        GLint texture { };                 /*!< TODO : Documentation */
        GLint sampler { };                 /*!< TODO : Documentation */
        GLint arrayBuffer { };             /*!< TODO : Documentation */
        GLint elementArrayBuffer { };      /*!< TODO : Documentation */
        GLint vertexArray { };             /*!< TODO : Documentation */
        GLint polygonMode[2] { };          /*!< TODO : Documentation */
        GLint viewport[4] { };             /*!< TODO : Documentation */
        GLint scissor[4] { };              /*!< TODO : Documentation */
        GLenum blendSrcRgb { };            /*!< TODO : Documentation */
        GLenum blendDstRgb { };            /*!< TODO : Documentation */
        GLenum blendSrcAlpha { };          /*!< TODO : Documentation */
        GLenum blendDstAlpha { };          /*!< TODO : Documentation */
        GLenum blendEquationRgb { };       /*!< TODO : Documentation */
        GLenum blendEquationAlpha { };     /*!< TODO : Documentation */
        GLboolean blendEnabled { };        /*!< TODO : Documentation */
        GLboolean cullFaceEnabled { };     /*!< TODO : Documentation */
        GLboolean depthTestEnabled { };    /*!< TODO : Documentation */
        GLboolean scissorTestEnabled { };  /*!< TODO : Documentation */

        /*
        * Records this State's snap shot of the current OpenGL state.
        */
        inline void stash()
        {
            dst_gl(glGetIntegerv(GL_ACTIVE_TEXTURE, reinterpret_cast<GLint*>(&activeTexture)));
            dst_gl(GL_TEXTURE0);
            dst_gl(glGetIntegerv(GL_CURRENT_PROGRAM, &program));
            dst_gl(glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture));
            dst_gl(glGetIntegerv(GL_SAMPLER_BINDING, &sampler));
            dst_gl(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &arrayBuffer));
            dst_gl(glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &elementArrayBuffer));
            dst_gl(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vertexArray));
            dst_gl(glGetIntegerv(GL_POLYGON_MODE, polygonMode));
            dst_gl(glGetIntegerv(GL_VIEWPORT, viewport));
            dst_gl(glGetIntegerv(GL_SCISSOR_BOX, scissor));
            dst_gl(glGetIntegerv(GL_BLEND_SRC_RGB, reinterpret_cast<GLint*>(&blendSrcRgb)));
            dst_gl(glGetIntegerv(GL_BLEND_DST_RGB, reinterpret_cast<GLint*>(&blendDstRgb)));
            dst_gl(glGetIntegerv(GL_BLEND_SRC_ALPHA, reinterpret_cast<GLint*>(&blendSrcAlpha)));
            dst_gl(glGetIntegerv(GL_BLEND_DST_ALPHA, reinterpret_cast<GLint*>(&blendDstAlpha)));
            dst_gl(glGetIntegerv(GL_BLEND_EQUATION_RGB, reinterpret_cast<GLint*>(&blendEquationRgb)));
            dst_gl(glGetIntegerv(GL_BLEND_EQUATION_ALPHA, reinterpret_cast<GLint*>(&blendEquationAlpha)));
            dst_gl(blendEnabled = glIsEnabled(GL_BLEND));
            dst_gl(cullFaceEnabled = glIsEnabled(GL_CULL_FACE));
            dst_gl(depthTestEnabled = glIsEnabled(GL_DEPTH_TEST));
            dst_gl(scissorTestEnabled = glIsEnabled(GL_SCISSOR_TEST));
        }

        /*
        * Sets the OpenGL state to this State's recorded snap shot.
        */
        inline void apply() const
        {
            dst_gl(glActiveTexture(activeTexture));
            dst_gl(glUseProgram(program));
            dst_gl(glBindTexture(GL_TEXTURE_2D, texture));
            dst_gl(glBindSampler(0, sampler));
            dst_gl(glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer));
            dst_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer));
            dst_gl(glBindVertexArray(vertexArray));
            dst_gl(glPolygonMode(GL_FRONT_AND_BACK, polygonMode[0]));
            dst_gl(glViewport(viewport[0], viewport[1], static_cast<GLsizei>(viewport[2]), static_cast<GLsizei>(viewport[3])));
            dst_gl(glScissor(scissor[0], scissor[1], static_cast<GLsizei>(scissor[2]), static_cast<GLsizei>(scissor[3])));
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

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
