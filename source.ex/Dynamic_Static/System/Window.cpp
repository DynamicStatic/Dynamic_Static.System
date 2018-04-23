
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Window.hpp"

#include "GLFW/glfw3.h"

#include "imgui.h"

#include <iostream>

namespace Dynamic_Static {
namespace System {

    GLFWwindow* gWindow;
    Window::Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
        gWindow = glfwCreateWindow(512, 512, "====", nullptr, nullptr);
        glfwMakeContextCurrent(gWindow);
    }

    Window::~Window()
    {
        glfwDestroyWindow(gWindow);
        std::cout << "~Window" << std::endl;
        glfwTerminate();
    }

} // namespace System
} // namespace Dynamic_Static
