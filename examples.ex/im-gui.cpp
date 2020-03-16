
/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace dst::sys;
    Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static ImGui";
    windowInfo.graphicsApi = GraphicsApi::OpenGL;
    windowInfo.glContextInfo.version = { 4, 5 };
    Window window(windowInfo);
    bool closeRequested = false;
    window.on_close_requested =
    [&](const Window&)
    {
        closeRequested = true;
    };

    gl::Gui gui;
    dst::Clock clock;
    while (!closeRequested && !window.input().keyboard.down(Keyboard::Key::Escape)) {
        clock.update();
        Window::poll_events();
        gui.begin_frame(clock, window);
        ImGui::ShowDemoWindow();
        auto viewport = window.info().extent;
        dst_gl(glViewport(0, 0, viewport.x, viewport.y));
        dst_gl(glClearColor(0, 0, 0, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT));
        gui.end_frame();
        gui.draw();
        window.swap();
    }
    return 0;
}
