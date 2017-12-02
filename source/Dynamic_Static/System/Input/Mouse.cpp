
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input/Mouse.hpp"
#include "../GLFWInclude.hpp"

namespace Dynamic_Static {
namespace System {

    Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton)
    {
        auto button = Mouse::Button::Unknown;
            switch (glfwMouseButton) {
                case GLFW_MOUSE_BUTTON_LEFT  : button = Mouse::Button::Left; break;
                case GLFW_MOUSE_BUTTON_RIGHT : button = Mouse::Button::Right; break;
                case GLFW_MOUSE_BUTTON_MIDDLE: button = Mouse::Button::Middle; break;
                case GLFW_MOUSE_BUTTON_4     : button = Mouse::Button::Unknown; break;
                case GLFW_MOUSE_BUTTON_5     : button = Mouse::Button::Unknown; break;
                case GLFW_MOUSE_BUTTON_6     : button = Mouse::Button::Unknown; break;
                case GLFW_MOUSE_BUTTON_7     : button = Mouse::Button::Unknown; break;
                case GLFW_MOUSE_BUTTON_LAST  : button = Mouse::Button::Unknown; break;
                default: button = Mouse::Button::Unknown;
            }

        return button;
    }

} // namespace System
} // namespace Dynamic_Static
