
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/OpenGL.hpp"
#include "Dynamic_Static/System/Video.hpp"

#include "imgui.h"

#include <array>
#include <string>

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over rendering an ImGui graphical user interface.
    */
    class Gui final
        : NonCopyable
    {
    private:
        gl::Texture mTexture;
        gl::Program mProgram;
        GLuint mProjectionLocation { 0 };
        gl::Mesh mMesh;

    public:
        /*
        * Constructs an instance of Gui.
        */
        inline Gui()
        {
            // TODO : Investiage ImGui::SetCurrentContext().

            ImGui::CreateContext();

            int fontWidth = 0;
            int fontHeight = 0;
            unsigned char* fontData = nullptr;
            auto& io = ImGui::GetIO();
            io.Fonts->GetTexDataAsAlpha8(&fontData, &fontWidth, &fontHeight);
            gl::Texture::Info textureInfo { };
            textureInfo.format = GL_RED;
            textureInfo.width = fontWidth;
            textureInfo.height = fontHeight;
            mTexture = gl::Texture(textureInfo, fontData);
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

            io.KeyMap[ImGuiKey_Tab]        = static_cast<int>(Keyboard::Key::Tab);
            io.KeyMap[ImGuiKey_LeftArrow]  = static_cast<int>(Keyboard::Key::LeftArrow);
            io.KeyMap[ImGuiKey_RightArrow] = static_cast<int>(Keyboard::Key::RightArrow);
            io.KeyMap[ImGuiKey_UpArrow]    = static_cast<int>(Keyboard::Key::UpArrow);
            io.KeyMap[ImGuiKey_DownArrow]  = static_cast<int>(Keyboard::Key::DownArrow);
            io.KeyMap[ImGuiKey_PageUp]     = static_cast<int>(Keyboard::Key::PageUp);
            io.KeyMap[ImGuiKey_PageDown]   = static_cast<int>(Keyboard::Key::PageDown);
            io.KeyMap[ImGuiKey_Home]       = static_cast<int>(Keyboard::Key::Home);
            io.KeyMap[ImGuiKey_End]        = static_cast<int>(Keyboard::Key::End);
            io.KeyMap[ImGuiKey_Delete]     = static_cast<int>(Keyboard::Key::Delete);
            io.KeyMap[ImGuiKey_Backspace]  = static_cast<int>(Keyboard::Key::Backspace);
            io.KeyMap[ImGuiKey_Enter]      = static_cast<int>(Keyboard::Key::Enter);
            io.KeyMap[ImGuiKey_Escape]     = static_cast<int>(Keyboard::Key::Escape);
            io.KeyMap[ImGuiKey_A]          = static_cast<int>(Keyboard::Key::A);
            io.KeyMap[ImGuiKey_C]          = static_cast<int>(Keyboard::Key::C);
            io.KeyMap[ImGuiKey_V]          = static_cast<int>(Keyboard::Key::V);
            io.KeyMap[ImGuiKey_X]          = static_cast<int>(Keyboard::Key::X);
            io.KeyMap[ImGuiKey_Y]          = static_cast<int>(Keyboard::Key::Y);
            io.KeyMap[ImGuiKey_Z]          = static_cast<int>(Keyboard::Key::Z);
            io.GetClipboardTextFn = get_clipboard;
            io.SetClipboardTextFn = set_clipboard;
        }

    public:
        /*
        * Updates this Gui.
        * @param [in] clock The clock used to maintain update and drawing timing
        * @param [in] window The Window to draw this Gui on
        */
        inline void update(
            const Clock& clock,
            Window& window
        )
        {
            const auto& input = window.get_input();
            auto& io = ImGui::GetIO();
            auto resolution = window.get_resolution();
            io.DisplaySize = {
                static_cast<float>(resolution.width),
                static_cast<float>(resolution.height)
            };
            io.DisplayFramebufferScale = { 1, 1 };
            io.DeltaTime = clock.elapsed<dst::Second<float>>();
            io.MousePos.x = input.mouse.current.position.x;
            io.MousePos.y = input.mouse.current.position.y;
            io.MouseDown[0] = input.mouse.down(Mouse::Button::Left);
            io.MouseDown[1] = input.mouse.down(Mouse::Button::Right);
            io.MouseDown[2] = input.mouse.down(Mouse::Button::Middle);
            io.MouseWheel += static_cast<float>(input.mouse.get_scroll_delta());
            for (int i = 0; i < static_cast<int>(Keyboard::Key::Count); ++i) {
                io.KeysDown[i] = input.keyboard.down(static_cast<Keyboard::Key>(i));
            }
            for (auto codepoint : window.get_text_stream()) {
                io.AddInputCharacter(static_cast<ImWchar>(codepoint));
            }
            io.KeyAlt = input.keyboard.down(Keyboard::Key::Alt);
            io.KeyCtrl =
                input.keyboard.down(Keyboard::Key::LeftControl) ||
                input.keyboard.down(Keyboard::Key::RightControl);
            io.KeyShift =
                input.keyboard.down(Keyboard::Key::LeftShift) ||
                input.keyboard.down(Keyboard::Key::RightShift);
            io.KeySuper =
                input.keyboard.down(Keyboard::Key::LeftWindow) ||
                input.keyboard.down(Keyboard::Key::RightWindow);
            io.ClipboardUserData = &window;
            #if defined(DYNAMIC_STATIC_WINDOWS)
            io.ImeWindowHandle = window.get_hwnd();
            #endif
            ImGui::NewFrame();
        }

        /*
        * Draws this Gui on the Window passed in update().
        */
        inline void draw()
        {
            ImGui::Render();
            const auto& io = ImGui::GetIO();
            auto drawData = ImGui::GetDrawData();
            drawData->ScaleClipRects(io.DisplayFramebufferScale);

            gl::State glState;
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
                static_cast<GLsizei>(io.DisplaySize.x),
                static_cast<GLsizei>(io.DisplaySize.y)
            ));

            float projection[4][4] = {
                {  2.0f / io.DisplaySize.x, 0,                         0, 0 },
                {  0,                       2.0f / -io.DisplaySize.y,  0, 0 },
                {  0,                       0,                        -1, 0 },
                { -1,                       1,                         0, 1 }
            };
            mProgram.bind();
            dst_gl(glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, &projection[0][0]));

            for (int cmdList_i = 0; cmdList_i < drawData->CmdListsCount; ++cmdList_i) {
                auto cmdList = drawData->CmdLists[cmdList_i];
                mMesh.write<ImDrawVert, ImDrawIdx>(
                    { cmdList->VtxBuffer.Data, static_cast<size_t>(cmdList->VtxBuffer.Size) },
                    { cmdList->IdxBuffer.Data, static_cast<size_t>(cmdList->IdxBuffer.Size) }
                );
                const ImDrawIdx* indexPtr = 0;
                for (int cmd_i = 0; cmd_i < cmdList->CmdBuffer.Size; ++cmd_i) {
                    const auto& cmd = cmdList->CmdBuffer[cmd_i];
                    if (cmd.UserCallback) {
                        cmd.UserCallback(cmdList, &cmd);
                    } else {
                        dst_gl(glActiveTexture(GL_TEXTURE0));
                        reinterpret_cast<gl::Texture*>(cmd.TextureId)->bind();
                        dst_gl(glScissor(
                            static_cast<GLint>(cmd.ClipRect.x),
                            static_cast<GLint>(io.DisplaySize.y - cmd.ClipRect.w),
                            static_cast<GLsizei>(cmd.ClipRect.z - cmd.ClipRect.x),
                            static_cast<GLsizei>(cmd.ClipRect.w - cmd.ClipRect.y)
                        ));
                        mMesh.draw_indexed(cmd.ElemCount, indexPtr);
                    }
                    indexPtr += cmd.ElemCount;
                }
            }

            mProgram.unbind();
            glState.apply();
        }

    private:
        static inline const char* get_clipboard(void* userData)
        {
            thread_local std::string tlStr;
            tlStr.clear();
            if (userData) {
                tlStr = reinterpret_cast<Window*>(userData)->get_clipboard();
            }
            return tlStr.c_str();
        }

        static inline void set_clipboard(void* userData, const char* clipboard)
        {
            if (userData && clipboard) {
                reinterpret_cast<Window*>(userData)->set_clipboard(clipboard);
            }
        }
    };

} // namespace System
} // namespace Dynamic_Static

namespace dstgl {

    template <>
    void enable_vertex_attributes<ImDrawVert>()
    {
        dst::gl::enable_vertex_attributes<ImDrawVert, 3>({{
            { GL_FLOAT, 2 },
            { GL_FLOAT, 2 },
            { GL_UNSIGNED_BYTE, 4, GL_TRUE }
        }});
    }

} // namespace dstgl

#define DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION
#if defined(DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION)
#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#endif
