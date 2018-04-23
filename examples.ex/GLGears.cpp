
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
    dst::sys::Window window;
    std::cout << "hello world" << std::endl;

    glewExperimental = true;
    auto error = glewInit();
    auto str = glewGetErrorString(error);
    std::cout << str << std::endl;

    GLuint buffer = 0;
    dst_gl(glCreateBuffers(1, &buffer));
    dst_gl(glDeleteBuffers(1, &buffer));
    return 0;
}
