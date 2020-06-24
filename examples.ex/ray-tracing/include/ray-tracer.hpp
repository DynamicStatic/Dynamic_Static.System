
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

#include "ray.hpp"
#include "renderer.hpp"
#include "scene.hpp"

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/core/thread-pool.hpp"
#include "dynamic_static/core/time.hpp"
#include "dynamic_static/graphics/opengl/mesh.hpp"
#include "dynamic_static/graphics/opengl/program.hpp"
#include "dynamic_static/graphics/opengl/shader.hpp"
#include "dynamic_static/graphics/opengl/texture.hpp"

#include <array>
#include <atomic>
#include <cassert>
#include <mutex>
#include <vector>

namespace dst {
namespace gfx {
namespace gl {

template <>
inline void enable_vertex_attributes<glm::vec4>()
{
    enable_vertex_attributes<glm::vec4, 3>({{
        { GL_FLOAT, 4 },
    }});
}

} // namespace gl
} // namespace gfx
} // namespace dst

namespace rtow {

class RayTracer final
    : public Renderer
{
public:
    inline RayTracer(dst::sys::Window& window)
        : Renderer(window)
        , mVisualizer(window.get_info().extent)
        , mPixels((size_t)window.get_info().extent.x * (size_t)window.get_info().extent.y)
        , mProcessedPixelCount { mPixels.size() }
    {
    }

    float get_progress() const
    {
        return (float)mProcessedPixelCount / (float)mPixels.size();
    }

    template <typename DurationType>
    auto get_time_taken() const
    {
        return dst::duration_cast<DurationType>(mEndUpdateTimePoint.load() - mBeginUpdateTimePoint).count();
    }

    inline void update(const Scene& scene) override final
    {
        mBeginUpdateTimePoint = dst::HighResolutionClock::now();
        mEndUpdateTimePoint = mBeginUpdateTimePoint;
        assert(mpWindow);
        if (mpWindow) {
            mProcessedPixelCount = 0;
            Uniforms uniforms { };
            auto const& windowExtent = mpWindow->get_info().extent;
            auto aspectRatio = (float)windowExtent.x / windowExtent.y;
            uniforms.viewportExtent.y = 2.0f;
            uniforms.viewportExtent.x = uniforms.viewportExtent.y * aspectRatio;
            for (int32_t y = 0; y < windowExtent.y; ++y) {
                mThreadPool.push(
                    [&scene, windowExtent, uniforms, y, this]()
                    {
                        for (int32_t x = 0; x < windowExtent.x; ++x) {
                            auto pixelIndex = x + windowExtent.x * y;
                            auto u = (float)x / (float)windowExtent.x;
                            auto v = (float)y / (float)windowExtent.y;
                            mPixels[pixelIndex] = process_pixel(scene, uniforms, { u, v });
                            if (++mProcessedPixelCount == mPixels.size()) {
                                mEndUpdateTimePoint = dst::HighResolutionClock::now();
                            }
                        }
                    }
                );
            }
        }
    }

    inline void on_draw() override final
    {
        mVisualizer.draw(mPixels);
    }

private:
    ///////////////////////////////////////////////////////////////////////////////
    // This region of code is the RayTracer "fragment shader"
    struct Uniforms final
    {
        glm::vec2 viewportExtent { };
        float focalLength { 1.0 };
    };

    inline static glm::vec3 get_ray_color(const Ray& ray, const Scene& scene)
    {
        Hittable::Record record { };
        if (scene.hittables.hit(ray, 0.0f, std::numeric_limits<float>::infinity(), record)) {
            return (record.normal + glm::vec3(1.0f)) * 0.5f;
        }
        glm::vec3 direction = glm::normalize(ray.direction);
        auto t = (direction.y + 1.0f) * 0.5f;
        return glm::lerp(glm::vec3(1.0f), glm::vec3(0.5f, 0.7f, 1.0f), t);
    }

    inline static glm::vec3 process_pixel(
        const Scene& scene,
        const Uniforms& uniforms,
        const glm::vec2& texCoord
    )
    {
        Ray ray { };
        glm::vec3 horizontal { uniforms.viewportExtent.x, 0, 0 };
        glm::vec3 vertical { 0, uniforms.viewportExtent.y, 0 };
        auto lowerLeftCorner = ray.origin - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0, 0, uniforms.focalLength);
        ray.direction = lowerLeftCorner + texCoord.x * horizontal + texCoord.y * vertical - ray.origin;
        return get_ray_color(ray, scene);
    }
    ///////////////////////////////////////////////////////////////////////////////

    class Visualizer final
    {
    public:
        inline Visualizer(const glm::ivec2& extent)
        {
            std::array<glm::vec4, 3> vertices {
                glm::vec4 { -1, -1, 0, 0 },
                glm::vec4 { -1,  3, 0, 2 },
                glm::vec4 {  3, -1, 2, 0 },
            };
            std::array<GLushort, 3> indices { 0, 1, 2 };
            mMesh.write<glm::vec4, GLushort>(vertices, indices);
            dst::gl::Texture::Info textureInfo { };
            textureInfo.format = GL_RGB;
            textureInfo.width = (GLsizei)extent.x;
            textureInfo.height = (GLsizei)extent.y;
            textureInfo.storageType = GL_FLOAT;
            mTexture = dst::gl::Texture(textureInfo);
            std::array<dst::gl::Shader, 2> shaders {{
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
            mProgram = dst::gl::Program(shaders);
        }

        inline void draw(const std::vector<glm::vec3>& pixels)
        {
            mTexture.write((const uint8_t*)pixels.data());
            dst_gl(glClear(GL_COLOR_BUFFER_BIT));
            dst_gl(glViewport(0, 0, (GLsizei)mTexture.info().width, (GLsizei)mTexture.info().height));
            mProgram.bind();
            dst_gl(glBindSampler(0, 0));
            dst_gl(glActiveTexture(GL_TEXTURE0));
            mTexture.bind();
            mMesh.draw_indexed();
        }

    private:
        dst::gl::Mesh mMesh;
        dst::gl::Texture mTexture;
        dst::gl::Program mProgram;
    } mVisualizer;

    dst::ThreadPool mThreadPool;
    std::vector<glm::vec3> mPixels;
    std::atomic_size_t mProcessedPixelCount { 0 };
    dst::TimePoint<> mBeginUpdateTimePoint;
    std::atomic<dst::TimePoint<>> mEndUpdateTimePoint;
};

} // namespace rtow

#if 0
namespace dst {
namespace gfx {
namespace gl {

template <>
inline void enable_vertex_attributes<glm::vec4>()
{
    enable_vertex_attributes<glm::vec4, 3>({{
        { GL_FLOAT, 4 },
    }});
}

} // namespace gl
} // namespace gfx
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
        uint32_t samplesPerPixel { 1 };
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
            #define USE_THREAD_POOL 1
            #if USE_THREAD_POOL
            mThreadPool.push(
            [y, &uniforms, this]()
            {
            #endif
                for (size_t x = 0; x < uniforms.extent.x; ++x) {
                    process_pixel(
                        uniforms,
                        glm::vec2 { x, y } / uniforms.extent,
                        mPixels[y * (size_t)uniforms.extent.x + x]
                    );
                }
            #if USE_THREAD_POOL
            });
            #endif
        }
        mThreadPool.wait();
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
    inline glm::vec3 get_color(const Ray& ray, const Hitable::Collection& world)
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
        glm::vec3 color { };
        for (uint32_t i = 0; i < uniforms.samplesPerPixel; ++i) {
            auto horizontal = uniforms.horizontal * texcoord.x;
            auto vertical = uniforms.vertical * texcoord.y;
            auto direction = uniforms.lowerLeftCorner + horizontal + vertical;
            pixel = get_color({ uniforms.origin, direction }, hitables);
        }
    }

    dst::gl::Mesh mMesh;
    dst::gl::Texture mTexture;
    std::vector<glm::vec3> mPixels;
    dst::gl::Program mProgram;
    Hitable::Collection hitables;
    dst::ThreadPool mThreadPool;
};
#endif
