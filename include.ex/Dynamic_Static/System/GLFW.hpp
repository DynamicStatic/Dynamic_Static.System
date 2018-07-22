
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)

#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
#include "Dynamic_Static/System/OpenGL.hpp"
#endif

#include "GLFW/glfw3.h"
#if defined(DYNAMIC_STATIC_WINDOWS)
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(DYNAMIC_STATIC_LINUX)
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
#endif
#include "GLFW/glfw3native.h"

namespace Dynamic_Static {
namespace System {
namespace detail {

    inline void glfw_error_callback(int error, const char* description)
    {

    }

    inline void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
    inline void glfw_char_callback(GLFWwindow* glfwWindow, unsigned int codepoint);
    inline void glfw_keyboard_callback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods);
    inline void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods);
    inline void glfw_mouse_position_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset);
    inline void glfw_mouse_scroll_callback(GLFWwindow* glfwWindow, double xOffset, double yOffset);

} // namespace Dynamic_Static
} // namespace System
} // namespace detail

#endif // defined(DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED)
