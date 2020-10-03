
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

#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"

namespace rtow {

class Rasterizer final
    : public Renderer
{
public:
    inline Rasterizer(dst::sys::Window& window)
        : Renderer(window)
    {
    }

    inline void update(const Camera& camera, const Scene& scene) override final
    {
    }

    inline void on_draw(const Camera& camera, const Scene& scene) override final
    {
        for (auto const& object : scene.hittables) {
            object->draw(camera);
        }
    }
};

} // namespace rtow
