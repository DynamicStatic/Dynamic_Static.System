
/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/gui.hpp"

namespace dst {
namespace sys {

Gui::Gui()
{
    ImGui::CreateContext();
    auto& io = ImGui::GetIO();
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

Gui::~Gui()
{
    ImGui::DestroyContext();
}

void Gui::begin_frame(const Clock& clock, Window& window)
{
    const auto& input = window.input();
    auto& io = ImGui::GetIO();
    auto resolution = window.info().extent;
    io.DisplaySize.x = (float)resolution.x;
    io.DisplaySize.y = (float)resolution.y;
    io.DisplayFramebufferScale = { 1, 1 };
    io.DeltaTime = clock.elapsed<dst::Seconds<float>>();
    io.MousePos.x = input.mouse.current.position.x;
    io.MousePos.y = input.mouse.current.position.y;
    io.MouseDown[0] = input.mouse.down(Mouse::Button::Left);
    io.MouseDown[1] = input.mouse.down(Mouse::Button::Right);
    io.MouseDown[2] = input.mouse.down(Mouse::Button::Middle);
    io.MouseWheel += (float)input.mouse.scroll_delta();
    for (int i = 0; i < (int)Keyboard::Key::Count; ++i) {
        io.KeysDown[i] = input.keyboard.down((Keyboard::Key)i);
    }
    for (auto codepoint : window.text_stream()) {
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
    io.ImeWindowHandle = window.hwnd();
    #endif
    ImGui::NewFrame();
}

void Gui::end_frame()
{
}

const char* Gui::get_clipboard(void* pUserData)
{
    thread_local std::string tlStr;
    tlStr.clear();
    if (pUserData) {
        tlStr = ((Window*)pUserData)->get_clipboard();
    }
    return tlStr.c_str();
}

void Gui::set_clipboard(void* pUserData, const char* pClipboard)
{
    if (pUserData && pClipboard) {
        ((Window*)pUserData)->set_clipboard(pClipboard);
    }
}

} // namespace sys
} // namespace dst
