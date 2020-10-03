
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
    using namespace dst;
    using namespace dst::sys;
    Window::GlInfo glInfo { };
    Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static ImGui";
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
    dst::Clock clock;
    while (!closeRequested && !window.get_input().keyboard.down(Keyboard::Key::Escape)) {
        clock.update();
        Window::poll_events();
        gui.begin_frame(clock, window);
        ImGui::ShowDemoWindow();
        auto viewport = window.get_info().extent;
        dst_gl(glViewport(0, 0, viewport.x, viewport.y));
        dst_gl(glClearColor(0, 0, 0, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT));
        gui.end_frame();
        gui.draw();
        window.swap();
    }
    return 0;
}
