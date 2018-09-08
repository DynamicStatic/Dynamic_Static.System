
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
#include "Dynamic_Static/System/Window.hpp"

#include "imgui.h"

#include <array>
#include <string>

namespace Dynamic_Static {
namespace System {

    /*!
    Provides high level control over rendering an ImGui graphical user interface.
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
        /*!
        Constructs an instance of Gui.
        */
        Gui();

    public:
        /*!
        Updates this Gui.
        @param [in] clock The clock used to maintain update and drawing timing
        @param [in] window The Window to draw this Gui on
        */
        void update(
            const Clock& clock,
            Window& window
        );

        /*!
        Draws this Gui on the Window passed in update().
        */
        void draw();

    private:
        static const char* get_clipboard(void* userData);
        static void set_clipboard(void* userData, const char* clipboard);
    };

} // namespace System
} // namespace Dynamic_Static

namespace dstgl {

    template <>
    inline void enable_vertex_attributes<ImDrawVert>()
    {
        dst::gl::enable_vertex_attributes<ImDrawVert, 3>({{
            { GL_FLOAT, 2 },
            { GL_FLOAT, 2 },
            { GL_UNSIGNED_BYTE, 4, GL_TRUE }
        }});
    }

} // namespace dstgl
