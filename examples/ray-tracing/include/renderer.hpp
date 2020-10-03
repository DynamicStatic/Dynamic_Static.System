
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
#include "scene.hpp"

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <functional>

namespace rtow {

class Renderer
{
public:
    inline Renderer(dst::sys::Window& window)
        : mpWindow { &window }
    {
        mpWindow->make_context_current();
    }

    virtual ~Renderer() = 0;
    virtual void update(const Camera& camera, const Scene& scene) = 0;
    inline void draw(
        const Camera& camera,
        const Scene& scene,
        const std::function<void()>& preDrawFunction = nullptr,
        const std::function<void()>& postDrawFunction = nullptr
    )
    {
        mpWindow->make_context_current();
        //dst_gl(glEnable(GL_CULL_FACE));
        //dst_gl(glCullFace(GL_BACK));
        //dst_gl(glEnable(GL_DEPTH_TEST));
        // dst_gl(glViewport(0, 0, viewport.x, viewport.y));
        dst_gl(glViewport(0, 0, camera.extent.x, camera.extent.y));
        dst_gl(glClearColor(0.1f, 0.1f, 0.1f, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        if (preDrawFunction) {
            preDrawFunction();
        }
        on_draw(camera, scene);
        if (postDrawFunction) {
            postDrawFunction();
        }
        mpWindow->swap();
    }

protected:
    virtual void on_draw(const Camera& camera, const Scene& scene) = 0;
    dst::sys::Window* mpWindow;
};

inline Renderer::~Renderer()
{
}

} // namespace rtow
