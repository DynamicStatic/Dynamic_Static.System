
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static.Core.hpp"
// #define DYNAMIC_STATIC_SYSTEM_IMPLEMENTATION
#include "Dynamic_Static.System.hpp"

int main()
{
    using namespace dst::sys;
    Window::Info windowInfo { };
    windowInfo.name = "Dynamic_Static BasicGui";
    windowInfo.graphicsApi = GraphicsApi::OpenGL;
    windowInfo.glContextInfo.version = { 4, 5 };
    Window window(windowInfo);
    bool running = true;
    window.on_close =
        [&](const IWindow&)
        {
            running = false;
        };

    dst::sys::Gui gui;
    dst::Clock clock;
    while (running) {
        clock.update();
        Window::poll_events();
        auto deltaTime = clock.elapsed<dst::Second<float>>();
        const auto& input = window.get_input();
        if (input.keyboard.down(Keyboard::Key::Escape)) {
            running = false;
        }
        gui.update(clock, window);
        ImGui::ShowDemoWindow();
        window.make_context_current();
        gui.draw();
        window.swap();
    }
    return 0;
}
