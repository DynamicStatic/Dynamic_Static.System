
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

// FROM : Based on Peter Shirley's "Ray Tracing in One Weekend" series
//  https://raytracing.github.io/

#pragma once

#include "hittable.hpp"
#include "ray.hpp"

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/graphics/opengl/program.hpp"
#include "dynamic_static/graphics/opengl/shader.hpp"

#include <string>

namespace rtow {

class Material
{
public:
    inline Material()
    {
        std::array<dst::gl::Shader, 2> shaders {{
            {
                GL_VERTEX_SHADER,
                __LINE__,
                R"(
                    #version 330
                    uniform mat4 model;
                    uniform mat4 view;
                    uniform mat4 projection;
                    layout(location = 0) in vec3 vertex;
                    out vec3 color;
                    void main()
                    {
                        gl_Position = projection * view * model * vec4(vertex, 1);
                    }
                )"
            },
            {
                GL_FRAGMENT_SHADER,
                __LINE__,
                R"(
                    #version 330
                    uniform vec3 albedo;
                    out vec4 fragColor;
                    void main()
                    {
                        fragColor = vec4(albedo, 1);
                    }
                )"
            }
        }};
        mProgram = dst::gl::Program(shaders);
    }

    virtual ~Material() = 0;
    virtual bool scatter(
        const Ray& ray,
        const Hittable::Record& record,
        glm::vec3& attenuation,
        Ray& scatteredRay
    ) const = 0;

    virtual void gui()
    {
    }

    GLint get_uniform_location(const std::string& uniformName) const
    {
        return mProgram.uniform_location(uniformName.c_str());
    }

    inline virtual void bind() const
    {
        mProgram.bind();
    }

    inline void unbind() const
    {
        mProgram.unbind();
    }

protected:
    dst::gl::Program mProgram;
};

inline Material::~Material()
{
}

} // namespace rtow
