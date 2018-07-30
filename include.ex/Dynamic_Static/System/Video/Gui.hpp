
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
#include "Dynamic_Static/System/OpenGL.hpp"

#include "imgui.h"

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over rendering an ImGui graphical user interface.
    */
    class Gui final
    {
    private:
        gl::Texture mFontTexture;

    public:
        Gui()
        {
            int fontWidth = 0;
            int fontHeight = 0;
            unsigned char* fontData = nullptr;
            auto& io = ImGui::GetIO();
            io.Fonts->GetTexDataAsAlpha8(&fontData, &fontWidth, &fontHeight);
            // io.Fonts->TexID = 
        }
    };

} // namespace System
} // namespace Dynamic_Static

#define DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION
#if defined(DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION)
#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#endif
