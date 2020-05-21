
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "ray-tracer.hpp"

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

int main(int argc, char* argv[])
{
    using namespace dst;
    using namespace dst::sys;
    Window::GlInfo glInfo { };
    Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static Ray Tracing";
    windowInfo.extent.x = 1200;
    windowInfo.extent.y = 600;
    windowInfo.pGlInfo = &glInfo;
    Window window(windowInfo);
    Delegate<const Window&> window_close_requested_handler;
    window.on_close_requested += window_close_requested_handler;
    bool closeRequested = false;
    window_close_requested_handler =
        [&](const Window&)
        {
            closeRequested = true;
        };

    gl::Gui gui;
    ImGui::GetIO().IniFilename = nullptr;
    RayTracer rayTracer(window.info().extent);
    dst::Clock clock;
    while (!closeRequested && !window.input().keyboard.down(Keyboard::Key::Escape)) {
        clock.update();
        Window::poll_events();
        gui.begin_frame(clock, window);
        // ImGui::Checkbox("Animation", &renderer.animation);
        // ImGui::Checkbox("Wireframe", &renderer.wireFrame);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if (ImGui::GetIO().WantCaptureMouse) {
            window.input().revert();
        }
        gui.end_frame();
        rayTracer.update(window.input());
        rayTracer.draw(window.info().extent);
        gui.draw();
        window.swap();
    }
    return 0;
}
