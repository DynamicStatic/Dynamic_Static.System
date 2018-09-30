
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Gui.hpp"

namespace dst {
namespace sys {

    Gui::Gui()
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

        io.KeyMap[ImGuiKey_Tab]        = (int)Keyboard::Key::Tab;
        io.KeyMap[ImGuiKey_LeftArrow]  = (int)Keyboard::Key::LeftArrow;
        io.KeyMap[ImGuiKey_RightArrow] = (int)Keyboard::Key::RightArrow;
        io.KeyMap[ImGuiKey_UpArrow]    = (int)Keyboard::Key::UpArrow;
        io.KeyMap[ImGuiKey_DownArrow]  = (int)Keyboard::Key::DownArrow;
        io.KeyMap[ImGuiKey_PageUp]     = (int)Keyboard::Key::PageUp;
        io.KeyMap[ImGuiKey_PageDown]   = (int)Keyboard::Key::PageDown;
        io.KeyMap[ImGuiKey_Home]       = (int)Keyboard::Key::Home;
        io.KeyMap[ImGuiKey_End]        = (int)Keyboard::Key::End;
        io.KeyMap[ImGuiKey_Delete]     = (int)Keyboard::Key::Delete;
        io.KeyMap[ImGuiKey_Backspace]  = (int)Keyboard::Key::Backspace;
        io.KeyMap[ImGuiKey_Enter]      = (int)Keyboard::Key::Enter;
        io.KeyMap[ImGuiKey_Escape]     = (int)Keyboard::Key::Escape;
        io.KeyMap[ImGuiKey_A]          = (int)Keyboard::Key::A;
        io.KeyMap[ImGuiKey_C]          = (int)Keyboard::Key::C;
        io.KeyMap[ImGuiKey_V]          = (int)Keyboard::Key::V;
        io.KeyMap[ImGuiKey_X]          = (int)Keyboard::Key::X;
        io.KeyMap[ImGuiKey_Y]          = (int)Keyboard::Key::Y;
        io.KeyMap[ImGuiKey_Z]          = (int)Keyboard::Key::Z;
        io.GetClipboardTextFn = get_clipboard;
        io.SetClipboardTextFn = set_clipboard;
    }

    void Gui::update(
        const Clock& clock,
        Window& window
    )
    {
        const auto& input = window.get_input();
        auto& io = ImGui::GetIO();
        auto resolution = window.get_resolution();
        io.DisplaySize.x = (float)resolution.x;
        io.DisplaySize.y = (float)resolution.y;
        io.DisplayFramebufferScale = { 1, 1 };
        io.DeltaTime = clock.elapsed<dst::Second<float>>();
        io.MousePos.x = input.mouse.current.position.x;
        io.MousePos.y = input.mouse.current.position.y;
        io.MouseDown[0] = input.mouse.down(Mouse::Button::Left);
        io.MouseDown[1] = input.mouse.down(Mouse::Button::Right);
        io.MouseDown[2] = input.mouse.down(Mouse::Button::Middle);
        io.MouseWheel += (float)input.mouse.get_scroll_delta();
        for (int i = 0; i < (int)Keyboard::Key::Count; ++i) {
            io.KeysDown[i] = input.keyboard.down((Keyboard::Key)i);
        }
        for (auto codepoint : window.get_text_stream()) {
            io.AddInputCharacter((ImWchar)codepoint);
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
        #ifdef DYNAMIC_STATIC_WINDOWS
        io.ImeWindowHandle = window.get_hwnd();
        #endif
        ImGui::NewFrame();
    }

    void Gui::draw()
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
            (GLsizei)io.DisplaySize.x,
            (GLsizei)io.DisplaySize.y
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
                { cmdList->VtxBuffer.Data, (size_t)(cmdList->VtxBuffer.Size) },
                { cmdList->IdxBuffer.Data, (size_t)(cmdList->IdxBuffer.Size) }
            );
            const ImDrawIdx* indexPtr = 0;
            for (int cmd_i = 0; cmd_i < cmdList->CmdBuffer.Size; ++cmd_i) {
                const auto& cmd = cmdList->CmdBuffer[cmd_i];
                if (cmd.UserCallback) {
                    cmd.UserCallback(cmdList, &cmd);
                } else {
                    dst_gl(glActiveTexture(GL_TEXTURE0));
                    ((gl::Texture*)cmd.TextureId)->bind();
                    dst_gl(glScissor(
                        (GLint)(cmd.ClipRect.x),
                        (GLint)(io.DisplaySize.y - cmd.ClipRect.w),
                        (GLsizei)(cmd.ClipRect.z - cmd.ClipRect.x),
                        (GLsizei)(cmd.ClipRect.w - cmd.ClipRect.y)
                    ));
                    mMesh.draw_indexed(cmd.ElemCount, indexPtr);
                }
                indexPtr += cmd.ElemCount;
            }
        }

        mProgram.unbind();
        glState.apply();
    }

    const char* Gui::get_clipboard(void* userData)
    {
        thread_local std::string tlStr;
        tlStr.clear();
        if (userData) {
            tlStr = ((Window*)userData)->get_clipboard();
        }
        return tlStr.c_str();
    }

    void Gui::set_clipboard(void* userData, const char* clipboard)
    {
        if (userData && clipboard) {
            ((Window*)userData)->set_clipboard(clipboard);
        }
    }

} // namespace sys
} // namespace dst
