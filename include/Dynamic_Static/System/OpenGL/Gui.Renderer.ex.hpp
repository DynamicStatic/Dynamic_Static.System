#if 0
/*
==========================================
  Copyright (c) 2017-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

#include "Dynamic_Static/System/OpenGL/Defines.hpp"
#include "Dynamic_Static/System/OpenGL/Mesh.hpp"
#include "Dynamic_Static/System/OpenGL/Program.hpp"
#include "Dynamic_Static/System/OpenGL/State.hpp"
#include "Dynamic_Static/System/OpenGL/Texture.hpp"
#include "Dynamic_Static/System/Gui.hpp"

#include <array>

namespace dst {
namespace sys {
namespace gl {

    /*!
    OpenGL implementation of Gui::Renderer
    */
    class GuiRenderer final
        : public Gui::Renderer
    {
    private:
        Texture mTexture;
        Program mProgram;
        GLuint mProjectionLocation { 0 };
        Mesh mMesh;

    public:
        /*!
        Constructs an instance of GuiRenderer
        \n NOTE : An OpenGL context must be created before creating a GuiRenderer
        */
        inline GuiRenderer()
        {
            // TODO : Investigate ImGui::SetCurrentContext()
            ImGui::CreateContext();

            int fontWidth = 0;
            int fontHeight = 0;
            unsigned char* fontData = nullptr;
            auto& io = ImGui::GetIO();
            io.Fonts->GetTexDataAsAlpha8(&fontData, &fontWidth, &fontHeight);
            Texture::Info textureInfo { };
            textureInfo.format = GL_RED;
            textureInfo.width = fontWidth;
            textureInfo.height = fontHeight;
            mTexture = Texture(textureInfo, fontData);
            io.Fonts->TexID = &mTexture;

            std::array<gl::Shader, 2> shaders {{
                {
                    GL_VERTEX_SHADER,
                    __LINE__,
                    R"(
                        #version 330
                        uniform mat4 projection;
                        in vec2 vsPosition;
                        in vec2 vsTexCoord;
                        in vec4 vsColor;
                        out vec2 fsTexCoord;
                        out vec4 fsColor;
                        void main()
                        {
                            gl_Position = projection * vec4(vsPosition.xy, 0, 1);
                            fsTexCoord = vsTexCoord;
                            fsColor = vsColor;
                        }
                    )"
                },
                {
                    GL_FRAGMENT_SHADER,
                    __LINE__,
                    R"(
                        #version 330
                        uniform sampler2D image;
                        in vec2 fsTexCoord;
                        in vec4 fsColor;
                        out vec4 fragColor;
                        void main()
                        {
                            fragColor = texture(image, fsTexCoord).rrrr * fsColor;
                        }
                    )"
                }
            }};
            mProgram = gl::Program(shaders);
            mProjectionLocation = mProgram.get_uniform_location("projection");
        }

    private:
        inline void draw() override final
        {
            ImGui::Render();
            const auto& io = ImGui::GetIO();
            auto drawData = ImGui::GetDrawData();
            drawData->ScaleClipRects(io.DisplayFramebufferScale);

            State glState;
            glState.stash();
            dst_gl(glBindSampler(0, 0));
            dst_gl(glEnable(GL_BLEND));
            dst_gl(glBlendEquation(GL_FUNC_ADD));
            dst_gl(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
            dst_gl(glDisable(GL_CULL_FACE));
            dst_gl(glDisable(GL_DEPTH_TEST));
            dst_gl(glEnable(GL_SCISSOR_TEST));
            dst_gl(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
            dst_gl(glViewport(
                0,
                0,
                (GLsizei)io.DisplaySize.x,
                (GLsizei)io.DisplaySize.y
            ));

            mProgram.bind();
            float projection[4][4] = {
                {  2.0f / io.DisplaySize.x, 0,                         0, 0 },
                {  0,                       2.0f / -io.DisplaySize.y,  0, 0 },
                {  0,                       0,                        -1, 0 },
                { -1,                       1,                         0, 1 }
            };
            dst_gl(glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, &projection[0][0]));
            for (int cmdList_i = 0; cmdList_i < drawData->CmdListsCount; ++cmdList_i) {
                auto cmdList = drawData->CmdLists[cmdList_i];
                mMesh.write<ImDrawVert, ImDrawIdx>(
                    { cmdList->VtxBuffer.Data, (size_t)cmdList->VtxBuffer.Size },
                    { cmdList->IdxBuffer.Data, (size_t)cmdList->IdxBuffer.Size }
                );
                const ImDrawIdx* indexPtr = 0;
                for (int cmd_i = 0; cmd_i < cmdList->CmdBuffer.Size; ++cmd_i) {
                    const auto& cmd = cmdList->CmdBuffer[cmd_i];
                    dst_gl(glActiveTexture(GL_TEXTURE0));
                    ((Texture*)cmd.TextureId)->bind();
                    dst_gl(glScissor(
                        (GLint)cmd.ClipRect.x,
                        (GLint)(io.DisplaySize.y - cmd.ClipRect.w),
                        (GLsizei)(cmd.ClipRect.z - cmd.ClipRect.x),
                        (GLsizei)(cmd.ClipRect.w - cmd.ClipRect.y)
                    ));
                    mMesh.draw_indexed(cmd.ElemCount, indexPtr);
                    indexPtr += cmd.ElemCount;
                }
            }
            mProgram.unbind();

            glState.apply();
        }
    };

    /*!
    Enables vertex attributes for ImDrawVert
    */
    template <>
    inline void enable_vertex_attributes<ImDrawVert>()
    {
        dst::gl::enable_vertex_attributes<ImDrawVert, 3>({ {
            { GL_FLOAT, 2 },
            { GL_FLOAT, 2 },
            { GL_UNSIGNED_BYTE, 4, GL_TRUE }
        } });
    }

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#endif