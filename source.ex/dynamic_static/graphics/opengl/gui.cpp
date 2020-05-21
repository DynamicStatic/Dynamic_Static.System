
/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/graphics/opengl/gui.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/graphics/opengl/shader.hpp"

namespace dst {
namespace gfx {
namespace gl {

template <>
inline void enable_vertex_attributes<ImDrawVert>()
{
    enable_vertex_attributes<ImDrawVert, 3>({{
        { GL_FLOAT, 2 },
        { GL_FLOAT, 2 },
        { GL_UNSIGNED_BYTE, 4, GL_TRUE }
    }});
}

Gui::Gui()
{
    int fontWidth = 0;
    int fontHeight = 0;
    unsigned char* pFontData = nullptr;
    auto& io = ImGui::GetIO();
    io.Fonts->GetTexDataAsAlpha8(&pFontData, &fontWidth, &fontHeight);
    Texture::Info textureInfo { };
    textureInfo.format = GL_RED;
    textureInfo.width = fontWidth;
    textureInfo.height = fontHeight;
    mTexture = Texture(textureInfo, pFontData);
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
    mProjectionLocation = mProgram.uniform_location("projection");
}

Gui::~Gui()
{
}

void Gui::draw()
{
    ImGui::Render();
    const auto& io = ImGui::GetIO();
    auto drawData = ImGui::GetDrawData();
    drawData->ScaleClipRects(io.DisplayFramebufferScale);

    Context context;
    context.stash();
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
    context.apply();
}

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
