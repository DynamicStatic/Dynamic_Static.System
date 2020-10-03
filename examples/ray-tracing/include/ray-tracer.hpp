
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

#include "materials/material.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "utilities.hpp"

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <mutex>
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

    inline ~RayTracer()
    {
    }

    float get_progress() const
    {
        return (float)mProcessedPixelCount / (float)mPixels.size();
    }

    template <typename DurationType>
    auto get_time_taken() const
    {
        if (mProcessedPixelCount != mPixels.size()) {
            mEndUpdateTimePoint = dst::HighResolutionClock::now();
        }
        return dst::duration_cast<DurationType>(mEndUpdateTimePoint - mBeginUpdateTimePoint).count();
    }

    inline void update(const Camera& camera, const Scene& scene) override final
    {
        std::fill(mPixels.begin(), mPixels.end(), glm::vec3 { });
        mBeginUpdateTimePoint = dst::HighResolutionClock::now();
        mEndUpdateTimePoint = dst::HighResolutionClock::now();
        assert(mpWindow);
        if (mpWindow) {
            mProcessedPixelCount = 0;
            auto const& windowExtent = mpWindow->get_info().extent;
            Uniforms uniforms { };
            uniforms.camera = camera;
            uniforms.camera.extent = windowExtent;
            uniforms.camera.update();
            uniforms.maxRecursionDepth = maxRecursionDepth;
            uniforms.msaaSampleCount = msaaSampleCount;
            for (int32_t y = 0; y < windowExtent.y; ++y) {
                mThreadPool.push(
                    [&scene, windowExtent, uniforms, y, this]()
                    {
                        for (int32_t x = 0; x < windowExtent.x; ++x) {
                            auto u = (float)x / (float)windowExtent.x;
                            auto v = (float)y / (float)windowExtent.y;
                            auto pixel = process_pixel(scene, uniforms, { x, y }, { u, v });
                            mPixels[(size_t)(x + windowExtent.x * y)] = pixel;
                        }
                        mProcessedPixelCount += windowExtent.x;
                    }
                );
            }
        }
    }

    inline void on_draw(const Camera& camera, const Scene& scene) override final
    {
        mVisualizer.draw(mPixels);
    }

    inline void stop()
    {
        mStop = true;
        mThreadPool.wait();
    }

    int maxRecursionDepth { 32 };
    int msaaSampleCount { 1 };

private:
    ///////////////////////////////////////////////////////////////////////////////
    // This region of code is the RayTracer "fragment shader"
    struct Uniforms final
    {
        Camera camera { };
        int maxRecursionDepth { };
        int msaaSampleCount { };
    };

    inline static glm::vec3 get_ray_color(const Ray& ray, const Scene& scene, int depth)
    {
        if (0 <= depth) {
            Hittable::Record record { };
            if (scene.hittables.hit(ray, 0.001f, std::numeric_limits<float>::infinity(), record)) {
                Ray scatteredRay { };
                glm::vec3 attenuation { };
                if (record.pMaterial && record.pMaterial->scatter(ray, record, attenuation, scatteredRay)) {
                    return attenuation * get_ray_color(scatteredRay, scene, depth - 1);
                }
                return { };
            }
            glm::vec3 direction = glm::normalize(ray.direction);
            auto t = (direction.y + 1.0f) * 0.5f;
            return glm::lerp(glm::vec3(1.0f), glm::vec3(0.5f, 0.7f, 1.0f), t);
        }
        return { };
    }

    inline static glm::vec3 process_pixel(
        const Scene& scene,
        const Uniforms& uniforms,
        const glm::uvec2& imgCoord,
        const glm::vec2& texCoord
    )
    {
        glm::vec3 color { };
        const auto& camera = uniforms.camera;
        for (int sample_i = 0; sample_i < uniforms.msaaSampleCount; ++sample_i) {
            static const float MaxRandomValue = 1.0f - std::numeric_limits<float>::epsilon();
            auto u = (imgCoord.x + get_rng().range<float>(0.0f, MaxRandomValue)) / (float)(camera.extent.x - 1);
            auto v = (imgCoord.y + get_rng().range<float>(0.0f, MaxRandomValue)) / (float)(camera.extent.y - 1);
            color += get_ray_color(camera.get_ray({ u, v }), scene, uniforms.maxRecursionDepth);
        }
        return color / (float)uniforms.msaaSampleCount;
    }
    ///////////////////////////////////////////////////////////////////////////////

    class Visualizer final
    {
    public:
        inline Visualizer(const glm::ivec2& extent)
        {
            std::array<glm::vec4, 3> vertices {
                glm::vec4 { -1.0f, -1.0f, 0.0f, 0.0f },
                glm::vec4 { -1.0f,  3.0f, 0.0f, 2.0f },
                glm::vec4 {  3.0f, -1.0f, 2.0f, 0.0f },
            };
            std::array<GLushort, 3> indices { 0, 1, 2 };
            mMesh.write<glm::vec4, GLushort>(vertices, indices);
            dst::sys::gl::Texture::Info textureInfo { };
            textureInfo.format = GL_RGB;
            textureInfo.width = (GLsizei)extent.x;
            textureInfo.height = (GLsizei)extent.y;
            textureInfo.storageType = GL_FLOAT;
            mTexture = dst::sys::gl::Texture(textureInfo);
            std::array<dst::sys::gl::Shader, 2> shaders {{
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
            mProgram = dst::sys::gl::Program(shaders);
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
        dst::sys::gl::Mesh mMesh;
        dst::sys::gl::Texture mTexture;
        dst::sys::gl::Program mProgram;
    } mVisualizer;

    std::atomic_bool mStop { };
    dst::ThreadPool mThreadPool;
    std::vector<glm::vec3> mPixels;
    std::atomic_size_t mProcessedPixelCount { };
    dst::TimePoint<> mBeginUpdateTimePoint;
    mutable dst::TimePoint<> mEndUpdateTimePoint;
};

} // namespace rtow
