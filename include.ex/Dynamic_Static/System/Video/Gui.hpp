
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Time.hpp"
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
                        out vec2 fsTexCoord;
                        out vec4 fsColor;
                        void main()
                        {
                            gl_Position = projection * vec4(vsPosition.xy, 0, 1);
                            fsTexCoord =- vsTexCoord;
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
                            fragColor = texture(image, fsTexCoord) * fsColor;
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
        * TODO : Documentation.
        */
        inline void begin_frame(
            const Clock& clock,
            Window& window
        )
        {
            const auto& input = window.get_input();
            auto& io = ImGui::GetIO();
            auto resolution = window.get_resolution();
            io.DisplaySize = { static_cast<float>(resolution.width), static_cast<float>(resolution.height) };
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
        * TODO : Documentation.
        */
        inline void end_frame()
        {

        }

        /*
        * TODO : Documentation.
        */
        inline void render()
        {

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
            { GL_UNSIGNED_INT, 1 }
        }});
    }

} // namespace dstgl

#define DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION
#if defined(DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION)
#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#endif
