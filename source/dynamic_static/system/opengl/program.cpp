
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/opengl/program.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

#include "dynamic_static/system/opengl/shader.hpp"

#include <iostream>
#include <utility>

namespace dst {
namespace sys {
namespace gl {

Program::Program()
{
    set_name("GlProgram");
}

Program::Program(dst::Span<Shader> shaders)
{
    set_name("GlProgram");
    dst_gl(mHandle = glCreateProgram());
    for (const auto& shader : shaders) {
        dst_gl(glAttachShader(mHandle, shader.get_handle()));
    }
    dst_gl(glLinkProgram(mHandle));
    GLint linkStatus = 0;
    dst_gl(glGetProgramiv(mHandle, GL_LINK_STATUS, &linkStatus));
    if (linkStatus != GL_TRUE) {
        std::cerr << "Failed to link program" << std::endl;
        std::cerr << info_log() << std::endl;
        std::cerr << std::endl;
        dst_gl(glDeleteProgram(mHandle));
        mHandle = 0;
    }
}

Program::Program(Program&& other) noexcept
{
    *this = std::move(other);
}

Program::~Program()
{
    dst_gl(glDeleteProgram(mHandle));
}

Program& Program::operator=(Program&& other) noexcept
{
    assert(this != &other);
    Object::operator=(std::move(other));
    return *this;
}

std::string Program::info_log() const
{
    return get_info_log(mHandle, glGetProgramiv, glGetProgramInfoLog);
}

GLint Program::uniform_location(const std::string& uniformName) const
{
    GLint uniformLocation = 0;
    dst_gl(uniformLocation = glGetUniformLocation(mHandle, uniformName.c_str()));
    return uniformLocation;
}

void Program::bind() const
{
    dst_gl(glUseProgram(mHandle));
}

void Program::unbind() const
{
    dst_gl(glUseProgram(0));
}

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
