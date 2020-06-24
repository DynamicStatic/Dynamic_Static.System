
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

#include "scene.hpp"

#include "dynamic_static/graphics/opengl/defines.hpp"
#include "dynamic_static/system/window.hpp"

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
    virtual void update(const Scene& scene) = 0;
    inline void draw(
        const std::function<void()>& preDrawFunction = nullptr,
        const std::function<void()>& postDrawFunction = nullptr
    )
    {
        mpWindow->make_context_current();
        dst_gl(glClear(GL_COLOR_BUFFER_BIT));
        if (preDrawFunction) {
            preDrawFunction();
        }
        on_draw();
        if (postDrawFunction) {
            postDrawFunction();
        }
        mpWindow->swap();
    }

protected:
    virtual void on_draw() = 0;
    dst::sys::Window* mpWindow;
};

inline Renderer::~Renderer()
{
}

} // namespace rtow
