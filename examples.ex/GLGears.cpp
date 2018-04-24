
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/OpenGL.hpp"
#include "Dynamic_Static/System/Window.hpp"

#include <iostream>

int main()
{
    using namespace dst::sys;
    Window::Info windowInfo {};
    windowInfo.api = GraphicsApi::OpenGL;
    windowInfo.apiVersion = { 4, 0 };
    Window window(windowInfo);
    std::cout << "hello sys" << std::endl;

    GLuint buffer = 0;
    dst_gl(glCreateBuffers(1, &buffer));
    dst_gl(glDeleteBuffers(1, &buffer));

    bool hit = true;
    while (hit) {
        Window::poll_events();
        window.swap_buffers();
    }


    return 0;
}
