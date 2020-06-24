
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

#include "rasterizer.hpp"
#include "ray-tracer.hpp"
#include "scene.hpp"
#include "sphere.hpp"

#include "dynamic_static/core/time.hpp"
#include "dynamic_static/graphics/opengl/gui.hpp"
#include "dynamic_static/system/gui.hpp"
#include "dynamic_static/system/window.hpp"

int main(int argc, char* argv[])
{
    dst::sys::Window::GlInfo glInfo { };
    dst::sys::Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static Ray Tracing (Ray Traced View)";
    windowInfo.extent.x = 1280;
    windowInfo.extent.y = 720;
    windowInfo.pGlInfo = &glInfo;
    dst::sys::Window rayTracingWindow(windowInfo);
    windowInfo.pName = "Dynamic_Static Ray Tracing (Rasterized View)";
    dst::sys::Window rasterizingWindow(windowInfo);
    bool close = false;
    dst::Delegate<const dst::sys::Window&> on_window_close([&](const auto& window) { close = true; });
    rayTracingWindow.on_close_requested += on_window_close;
    rasterizingWindow.on_close_requested += on_window_close;
    rtow::Rasterizer rasterizer(rasterizingWindow);
    rtow::RayTracer rayTracer(rayTracingWindow);
    rasterizingWindow.make_context_current();
    dst::gl::Gui gui;
    ImGui::GetIO().IniFilename = nullptr;
    rtow::Scene scene;
    scene.hittables.push_back(std::make_unique<rtow::Sphere>(glm::vec3 { 0.0f, 0.0f, -1.0f }, 0.5f));
    scene.hittables.push_back(std::make_unique<rtow::Sphere>(glm::vec3 { 0.0f, -100.5f, -1.0f }, 100.0f));
    for (dst::Clock clock;
        !close &&
        !rasterizingWindow.get_input().keyboard.down(dst::sys::Keyboard::Key::Escape) &&
        !rayTracingWindow.get_input().keyboard.down(dst::sys::Keyboard::Key::Escape);
        clock.update()) {
        rasterizer.update(scene);
        rayTracer.draw();
        rasterizer.draw(
            [&]()
            {
                gui.begin_frame(clock, rasterizingWindow);
                if (rayTracer.get_progress() < 1.0f) {
                    ImGui::ProgressBar(rayTracer.get_progress());
                } else {
                    if (ImGui::Button("Update Ray Traced View")) {
                        rayTracer.update(scene);
                    }
                }
                ImGui::Text("Update time : %f ms", rayTracer.get_time_taken<dst::Milliseconds<float>>());
                ImGui::Text("Update time : %f s", rayTracer.get_time_taken<dst::Seconds<float>>());
                if (ImGui::GetIO().WantCaptureMouse) {
                    rasterizingWindow.get_input().revert();
                }
            },
            [&]()
            {
                gui.end_frame();
                gui.draw();
            }
        );
        dst::sys::Window::poll_events();
    }
    return 0;
}
