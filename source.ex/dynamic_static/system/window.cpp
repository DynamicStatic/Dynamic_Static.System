
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/window.hpp"

#include <mutex>
#include <set>
#include <utility>

namespace dst {
namespace sys {

template <typename FunctionType>
static inline void access_glfw_windows(FunctionType function)
{
    static std::mutex sMutex;
    static std::set<GLFWwindow*> sGlfwWindows;
    std::lock_guard<std::mutex> lock(sMutex);
    function(sGlfwWindows);
}

Window::Window(const CreateInfo& createInfo)
{

}

Window::Window(Window&& other)
{
    *this = std::move(other);
}

Window::~Window()
{

}

Window& Window::operator=(Window&& other)
{
    return *this;
}

#ifdef DYNAMIC_STATIC_WINDOWS
void* Window::get_hwnd() const
{
    return nullptr;
}
#endif // DYNAMIC_STATIC_WINDOWS

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED
void Window::make_context_current()
{

}

void Window::swap()
{

}
#endif // DYNAMIC_STATIC_OPENGL_ENABLED

} // namespace sys
} // namespace dst
