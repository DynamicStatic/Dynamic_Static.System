
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static.Core.hpp"
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
    [&](const Window&)
    {
        running = false;
    };

    Gui gui(std::make_unique<gl::GuiRenderer>());
    dst::Clock clock;
    while (running) {
        clock.update();
        Window::poll_events();
        const auto& input = window.get_input();
        if (input.keyboard.down(Keyboard::Key::Escape)) {
            running = false;
        }
        gui.begin_frame(clock, window);
        ImGui::ShowDemoWindow();
        window.make_context_current();
        auto resolution = window.get_resolution();
        dst_gl(glViewport(0, 0, resolution.x, resolution.y));
        dst_gl(glClearColor(0, 0, 0, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT));
        gui.draw();
        window.swap();
    }
    return 0;
}
