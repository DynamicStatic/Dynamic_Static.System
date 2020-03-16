
/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/system/opengl/mesh.hpp"
#include "dynamic_static/system/opengl/program.hpp"
#include "dynamic_static/system/opengl/texture.hpp"
#include "dynamic_static/system/gui.hpp"

namespace dst {
namespace sys {
namespace gl {

/**
TODO : Documentation
*/
class Gui final
    : public sys::Gui
{
public:
    /**
    Constructs an instance of Gui
    */
    Gui();

    /**
    Destroys this instance of Gui
    */
    ~Gui() override final;

    /**
    TODO : Documentation
    */
    void draw() override final;

private:
    Texture mTexture;
    Program mProgram;
    GLuint mProjectionLocation { 0 };
    Mesh mMesh;
};

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
