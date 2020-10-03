
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/graphics/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/graphics/opengl/object.hpp"

#include <string>

namespace dst {
namespace gfx {
namespace gl {

/**
Provides high level control over an OpenGL shader
*/
class Shader final
    : public Object
{
public:
    /**
    Constructs an instance of Shader
    */
    Shader();

    /**
    Constructs an instance of Shader
    TODO : Documentation
    */
    Shader(GLenum stage, const std::string& source);

    /**
    Constructs an instance of Shader
    TODO : Documentation
    */
    Shader(GLenum stage, int lineOffset, const std::string& source);

    /**
    Moves an instance of Shader
    @param [in] other The Shader to move from
    */
    Shader(Shader&& other) noexcept;

    /**
    Destroys this instance of Shader
    */
    ~Shader() override final;

    /**
    Moves an instance of Shader
    @param [in] other The Shader to move from
    @return A reference to this Shader
    */
    Shader& operator=(Shader&& other) noexcept;

    /**
    TODO : Documentation
    */
    std::string info_log();
};

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
