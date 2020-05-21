
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/graphics/opengl/shader.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

namespace dst {
namespace gfx {
namespace gl {

Shader::Shader()
{
    set_name("GlShader");
}

Shader::Shader(GLenum stage, const std::string& source)
    : Shader(stage, 0, source)
{
}

Shader::Shader(GLenum stage, int lineOffset, const std::string& source)
{
    set_name("GlShader");
    // TODO : lineOffset is _sometime_ incorrect...wtf?
    auto versionBegin = source.find("#version");
    auto versionEnd = source.find('\n', versionBegin);
    std::string headerStr(source.substr(versionBegin, versionEnd));
    std::string sourceStr(source.substr(versionEnd));
    auto lineCount = std::count(headerStr.begin(), headerStr.end(), '\n');
    headerStr += "#line " + std::to_string(lineOffset + lineCount) + "\n";
    auto modifiedSource = headerStr + sourceStr;
    auto sourceCStr = modifiedSource.c_str();
    dst_gl(mHandle = glCreateShader(stage));
    dst_gl(glShaderSource(mHandle, 1, &sourceCStr, nullptr));
    dst_gl(glCompileShader(mHandle));
    GLint compileStatus = 0;
    dst_gl(glGetShaderiv(mHandle, GL_COMPILE_STATUS, &compileStatus));
    if (compileStatus != GL_TRUE) {
        std::string stageStr;
        switch (stage) {
        case GL_VERTEX_SHADER:          stageStr = "GL_VERTEX_SHADER"; break;
        case GL_TESS_CONTROL_SHADER:    stageStr = "GL_TESS_CONTROL_SHADER"; break;
        case GL_TESS_EVALUATION_SHADER: stageStr = "GL_TESS_EVALUATION_SHADER"; break;
        case GL_GEOMETRY_SHADER:        stageStr = "GL_GEOMETRY_SHADER"; break;
        case GL_FRAGMENT_SHADER:        stageStr = "GL_FRAGMENT_SHADER"; break;
        case GL_COMPUTE_SHADER:         stageStr = "GL_COMPUTE_SHADER"; break;
        default: {
            assert(false);
            stageStr = "GL_UNKNOWN_SHADER";
        } break;
        }
        std::cerr << "Failed to compile " << stageStr << std::endl;
        std::cerr << info_log() << std::endl;
        std::cerr << std::endl;
        dst_gl(glDeleteShader(mHandle));
        mHandle = 0;
    }
}

Shader::Shader(Shader&& other) noexcept
{
    *this = std::move(other);
}

Shader::~Shader()
{
    dst_gl(glDeleteShader(mHandle));
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    assert(this != &other);
    Object::operator=(std::move(other));
    return *this;
}

std::string Shader::info_log()
{
    return get_info_log(mHandle, glGetShaderiv, glGetShaderInfoLog);
}

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
