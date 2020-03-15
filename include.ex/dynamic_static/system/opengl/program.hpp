
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/core/span.hpp"
#include "dynamic_static/system/opengl/object.hpp"

#include <string>

namespace dst {
namespace sys {
namespace gl {

class Shader;

/**
Provides high level control over an OpenGL program
*/
class Program final
    : public Object
{
public:
    /**
    Constructs an instance of Program
    */
    Program();

    /**
    Constructs an instance of Program
    TODO : Documentation
    */
    Program(dst::Span<Shader> shaders);

    /**
    Moves an instance of Program
    @param [in] other The Program to move from
    */
    Program(Program&& other) noexcept;

    /**
    Destroys this instance of Program
    */
    ~Program() override final;

    /**
    Moves an instance of Program
    @param [in] other The Program to move from
    @return A reference to this Program
    */
    Program& operator=(Program&& other) noexcept;

    /**
    TODO : Documentation
    */
    std::string info_log() const;

    /**
    TODO : Documentation
    */
    GLint uniform_location(const std::string& uniformName) const;

    /**
    TODO : Documentation
    */
    void bind() const;

    /**
    TODO : Documentation
    */
    void unbind() const;
};

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
