
/*
==========================================
    Copyright 2017-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)

#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/System/OpenGL/Defines.hpp"
#include "Dynamic_Static/System/OpenGL/Object.hpp"

#include <string>
#include <utility>

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*
    * Provides high level control over an OpenGL shader.
    */
    class Shader final
        : public Object
    {
    public:
        /*
        * Constructs an instance of Shader.
        */
        inline Shader()
        {
            set_name("Shader");
        }

        /*
        * Constructs an instance of Shader.
        * @param [in] stage This Shader's stage
        * @param [in] source This Shader's source
        */
        inline Shader(
            GLenum stage,
            dst::string_view source
        )
            : Shader(stage, 0, source)
        {
        }

        /*
        * Constructs an instance of Shader.
        * @param [in] stage This Shader's stage
        * @param [in] line The starting line to use for error reporting
        * @param [in] source This Shader's source
        */
        inline Shader(
            GLenum stage,
            int line,
            dst::string_view source
        )
        {
            // TODO : Line offset is _sometimes_ incorrect...wtf?
            auto versionPosition = source.find("#version");
            auto versionEnd = source.find('\n', versionPosition);
            // TODO : Setup dst::StringView to ensure null termination.
            //        See https://stackoverflow.com/a/41288372/3453616
            std::string sourceStr(source.substr(versionEnd));
            std::string headerStr(source.substr(versionPosition, versionEnd));
            auto lineCount = std::count(headerStr.begin(), headerStr.end(), '\n');
            headerStr += "#line " + std::to_string(line + lineCount) + "\n";
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
                    case GL_VERTEX_SHADER: stageStr = "vertex"; break;
                    case GL_TESS_CONTROL_SHADER: stageStr = "tesselation control"; break;
                    case GL_TESS_EVALUATION_SHADER: stageStr = "tesselation evaluation"; break;
                    case GL_GEOMETRY_SHADER: stageStr = "geometry"; break;
                    case GL_FRAGMENT_SHADER: stageStr = "fragment"; break;
                    case GL_COMPUTE_SHADER: stageStr = "compute"; break;
                    default: stageStr = "unknown";
                }
                // TODO : dst::core logging...
                std::cerr
                    << "Failed to compile " << stageStr << " shader" << std::endl
                    << get_info_log() << std::endl
                    << std::endl;
                dst_gl(glDeleteShader(mHandle));
                mHandle = 0;
            }
            set_name("Shader");
        }

        /*
        * Moves an instance of Shader.
        * @param [in] other The Shader to move from
        */
        inline Shader(Shader&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of Shader.
        */
        inline ~Shader()
        {
            if (mHandle) {
                dst_gl(glDeleteShader(mHandle));
            }
        }

        /*
        * Moves an instance of Shader.
        * @param [in] other The Shader to move from
        * @return This Shader
        */
        inline Shader& operator=(Shader&& other)
        {
            if (this != &other) {
                Object::operator=(std::move(other));
            }
            return *this;
        }

    public:
        /*
        * Gets this Shader's info log.
        * @return This Shader's info log
        */
        inline std::string get_info_log() const
        {
            return get_info_log(mHandle);
        }

        /*
        * Gets a given Shader's info log.
        * @param [in] shader The Shader to get the info log for
        * @return The given Shader's info log
        */
        static inline std::string get_info_log(const Shader& shader)
        {
            return get_info_log(shader.get_handle());
        }

        /*
        * Gets a given Shader's info log.
        * @param [in] handle The handle to the Shader to get the info log for
        * @return The given Shader's info log
        */
        static inline std::string get_info_log(GLuint handle)
        {
            return gl::get_info_log(handle, glGetShaderiv, glGetShaderInfoLog);
        }
    };

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
