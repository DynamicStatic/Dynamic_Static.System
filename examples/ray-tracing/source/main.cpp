
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

#include "materials/dialectric.hpp"
#include "materials/lambert.hpp"
#include "materials/metal.hpp"
#include "camera.hpp"
#include "rasterizer.hpp"
#include "ray-tracer.hpp"
#include "scene.hpp"
#include "sphere.hpp"

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

int main(int argc, char* argv[])
{
    dst::sys::Window::GlInfo glInfo { };
    dst::sys::Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static Ray Tracing (Ray Traced View)";
    #if 1
    windowInfo.extent.x = 960; // 1280;
    windowInfo.extent.y = 540; // 720;
    #else
    windowInfo.extent.x = 384;
    windowInfo.extent.y = (int32_t)((float)windowInfo.extent.x / (16.0f / 9.0f));
    #endif
    windowInfo.pGlInfo = &glInfo;
    dst::sys::Window rayTracingWindow(windowInfo);
    windowInfo.pName = "Dynamic_Static Ray Tracing (Rasterized View)";
    dst::sys::Window rasterizerWindow(windowInfo);
    bool close = false;
    dst::Delegate<const dst::sys::Window&> on_window_close([&](const auto& window) { close = true; });
    rayTracingWindow.on_close_requested += on_window_close;
    rasterizerWindow.on_close_requested += on_window_close;
    rtow::Rasterizer rasterizer(rasterizerWindow);
    rtow::RayTracer rayTracer(rayTracingWindow);

    rasterizerWindow.make_context_current();
    dst::sys::gl::Gui gui;
    rtow::Scene scene;
    rtow::Camera camera;

    // scene.hittables.push_back(
    //     std::make_unique<rtow::Sphere>(
    //         glm::vec3 { -1.0f, 0.0f, -1.0f },
    //         0.5f,
    //         std::make_unique<rtow::Dialectric>(1.5f)
    //     )
    // );
    // scene.hittables.push_back(
    //     std::make_unique<rtow::Sphere>(
    //         glm::vec3 { -1.0f, 0.0f, -1.0f },
    //         -0.45f,
    //         std::make_unique<rtow::Dialectric>(1.5f)
    //     )
    // );
    scene.hittables.push_back(
        std::make_unique<rtow::Sphere>(
            glm::vec3 { 0.0f, 0.0f, -1.0f },
            0.5f,
            std::make_unique<rtow::Lambert>(glm::vec3 { 0.1f, 0.2f, 0.5f })
        )
    );
    // scene.hittables.push_back(
    //     std::make_unique<rtow::Sphere>(
    //         glm::vec3 { 1.0f, 0.0f, -1.0f },
    //         0.5f,
    //         std::make_unique<rtow::Metal>(glm::vec3{ 0.8f, 0.6f, 0.2f }, 0.3f)
    //     )
    // );
    // scene.hittables.push_back(
    //     std::make_unique<rtow::Sphere>(
    //         glm::vec3 { 0.0f, -100.5f, -1.0f },
    //         100.0f,
    //         std::make_unique<rtow::Lambert>(glm::vec3 { 0.8f, 0.8f, 0.0f })
    //     )
    // );

    for (dst::Clock clock;
        !close &&
        !rasterizerWindow.get_input().keyboard.down(dst::sys::Keyboard::Key::Escape) &&
        !rayTracingWindow.get_input().keyboard.down(dst::sys::Keyboard::Key::Escape);
        clock.update()) {
        camera.extent = rayTracingWindow.get_info().extent;
        rayTracer.draw(camera, scene);
        camera.extent = rasterizerWindow.get_info().extent;
        rasterizer.update(camera, scene);
        rasterizer.draw(
            camera,
            scene,
            [&]()
            {
                gui.begin_frame(clock, rasterizerWindow);
                ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
                if (rayTracer.get_progress() < 1.0f) {
                    ImGui::ProgressBar(rayTracer.get_progress());
                } else {
                    if (ImGui::Button("Update Ray Traced View")) {
                        rayTracer.update(camera, scene);
                    }
                }
                ImGui::Text("Update time : %f ms", rayTracer.get_time_taken<dst::Milliseconds<float>>());
                ImGui::Text("Update time : %f s", rayTracer.get_time_taken<dst::Seconds<float>>());
                ImGui::Text("Update time : %f m", rayTracer.get_time_taken<dst::Minutes<float>>());
                ImGui::DragInt("Max Recursion Depth", &rayTracer.maxRecursionDepth, 1.0f, 1, 128);
                ImGui::DragInt("MSAA Sample Count", &rayTracer.msaaSampleCount, 1.0f, 1, 128);
                if (ImGui::GetIO().WantCaptureMouse) {
                    // rasterizerWindow.get_input().revert();
                }
                if (1 <= rayTracer.get_progress()) {
                    for (const auto& object : scene.hittables) {
                        ImGui::PushID(&object);
                        object->gui();
                        ImGui::PopID();
                    }
                }
            },
            [&]()
            {
                ImGui::End();
                gui.end_frame();
                gui.draw();
            }
        );
        camera.lookEnabled = rasterizerWindow.get_input().mouse.down(dst::sys::Mouse::Button::Left);
        camera.update(clock, rasterizerWindow.get_input());
#if 0
        const auto& input = rasterizerWindow.get_input();
        auto deltaTime = clock.elapsed<dst::Milliseconds<float>>();
        camera.transform.translation.z -= input.mouse.scroll_delta() * 0.1f * deltaTime;
        if (input.mouse.down(dst::sys::Mouse::Button::Middle) ||
            input.mouse.down(dst::sys::Mouse::Button::Right)) {
            camera.transform.translation.x -= input.mouse.position_delta().x * 0.004f * deltaTime;
            camera.transform.translation.y += input.mouse.position_delta().y * 0.004f * deltaTime;
        }
#endif
        dst::sys::Window::poll_events();
    }
    return 0;
}
