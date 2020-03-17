
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "hitable.hpp"
#include "ray.hpp"
#include "sphere.hpp"

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <array>
#include <limits>
#include <vector>

namespace dst {
namespace sys {
namespace gl {

template <>
inline void enable_vertex_attributes<glm::vec4>()
{
    enable_vertex_attributes<glm::vec4, 3>({{
        { GL_FLOAT, 4 },
    }});
}

} // namespace gl
} // namespace sys
} // namespace dst

class RayTracer final
{
public:
    struct Uniforms final
    {
        glm::vec3 lowerLeftCorner { -2, -1, -1 };
        glm::vec3 horizontal { 4, 0, 0 };
        glm::vec3 vertical { 0, 2, 0 };
        glm::vec3 origin { 0, 0, 0 };
        glm::vec2 extent { 0, 0 };
    };

    inline RayTracer(const glm::vec2& viewport)
    {
        using namespace dst::gl;
        std::array<glm::vec4, 3> vertices {
            glm::vec4 { -1, -1, 0, 0 },
            glm::vec4 { -1,  3, 0, 2 },
            glm::vec4 {  3, -1, 2, 0 },
        };
        std::array<GLushort, 3> indices { 0, 1, 2 };
        mMesh.write<glm::vec4, GLushort>(
            { vertices.data(), vertices.size() },
            { indices.data(), indices.size() }
        );
        Texture::Info textureInfo { };
        textureInfo.format = GL_RGB;
        textureInfo.width = (GLsizei)viewport.x;
        textureInfo.height = (GLsizei)viewport.y;
        textureInfo.storageType = GL_FLOAT;
        mTexture = Texture(textureInfo);
        mPixels.resize((size_t)textureInfo.width * (size_t)textureInfo.height);
        std::array<Shader, 2> shaders {{
            {
                GL_VERTEX_SHADER,
                __LINE__,
                R"(
                    #version 330
                    layout(location = 0) in vec4 vertex;
                    out vec2 fsTexCoord;
                    void main()
                    {
                        gl_Position = vec4(vertex.xy, 0, 1);
                        fsTexCoord = vertex.zw;
                    }
                )"
            },
            {
                GL_FRAGMENT_SHADER,
                __LINE__,
                R"(
                    #version 330
                    uniform sampler2D image;
                    in vec2 fsTexCoord;
                    out vec4 fragColor;
                    void main()
                    {
                        fragColor = texture(image, fsTexCoord);
                        fragColor.a = 1;
                    }
                )"
            }
        }};
        mProgram = Program(shaders);
        hitables.hitables.push_back(std::make_unique<Sphere>(glm::vec3(0, 0, -1), 0.5f));
        hitables.hitables.push_back(std::make_unique<Sphere>(glm::vec3(0, -100.5f, -1), 100.0f));
    }

    inline void update(const dst::sys::Input& input)
    {
        Uniforms uniforms { };
        uniforms.extent = { mTexture.info().width, mTexture.info().height };
        for (size_t y = 0; y < uniforms.extent.y; ++y) {
            for (size_t x = 0; x < uniforms.extent.x; ++x) {
                process_pixel(
                    uniforms,
                    glm::vec2 { x, y } / uniforms.extent,
                    mPixels[y * (size_t)uniforms.extent.x + x]
                );
            }
        }
    }

    inline void draw(const glm::vec2& viewport)
    {
        mTexture.write((const uint8_t*)mPixels.data());
        dst_gl(glClear(GL_COLOR_BUFFER_BIT));
        dst_gl(glViewport(0, 0, (GLsizei)viewport.x, (GLsizei)viewport.y));
        mProgram.bind();
        dst_gl(glBindSampler(0, 0));
        dst_gl(glActiveTexture(GL_TEXTURE0));
        mTexture.bind();
        mMesh.draw_indexed();
        mProgram.unbind();
    }

private:
    inline glm::vec3 color(const Ray& ray, const Hitable::Collection& world)
    {
        Hitable::Record record { };
        if (world.hit(ray, 0.0f, std::numeric_limits<float>::max(), record)) {
            return 0.5f * glm::vec3(record.normal.x + 1, record.normal.y + 1, record.normal.z + 1);
        } else {
            auto direction = glm::normalize(ray.direction);
            float t = (direction.y + 1.0f) * 0.5f;
            return (1.0f - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5f, 0.7f, 1.0f);
        }
    }

    inline void process_pixel(
        const Uniforms& uniforms,
        const glm::vec2& texcoord,
        glm::vec3& pixel
    )
    {
        auto horizontal = uniforms.horizontal * texcoord.x;
        auto vertical = uniforms.vertical * texcoord.y;
        auto direction = uniforms.lowerLeftCorner + horizontal + vertical;
        pixel = color({ uniforms.origin, direction }, hitables);
    }

    dst::gl::Mesh mMesh;
    dst::gl::Texture mTexture;
    std::vector<glm::vec3> mPixels;
    dst::gl::Program mProgram;
    Hitable::Collection hitables;
};
