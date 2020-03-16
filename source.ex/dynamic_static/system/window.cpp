
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/window.hpp"
#include "glfw-window.hpp"

#include <mutex>
#include <utility>

namespace dst {
namespace sys {

std::mutex Window::sMutex;
std::set<GLFWwindow*> Window::sGlfwWindows;

Window::Window(const Info& info)
    : mInfo { info }
{
    mGlfwWindow = create_glfw_window(info);
    glfwSetWindowUserPointer(mGlfwWindow, this);
    mName = info.pName ? info.pName : "Dynamic_Static";
    mInfo.pName = mName.c_str();
}

Window::Window(Window&& other) noexcept
{
    *this = std::move(other);
}

Window::~Window()
{
    destroy_glfw_window(mGlfwWindow);
}

Window& Window::operator=(Window&& other) noexcept
{
    assert(this != &other);
    mInfo = std::move(other.mInfo);
    mInput = std::move(other.mInput);
    mTextStream = std::move(other.mTextStream);
    mName = std::move(other.mName);
    mGlfwWindow = std::move(other.mGlfwWindow);
    other.mGlfwWindow = nullptr;
    return *this;
}

const Window::Info& Window::info() const
{
    return mInfo;
}

const Input& Window::input() const
{
    return mInput;
}

#ifdef DYNAMIC_STATIC_WINDOWS
void* Window::hwnd() const
{
    return glfwGetWin32Window(mGlfwWindow);
}
#endif // DYNAMIC_STATIC_WINDOWS

std::string Window::get_clipboard() const
{
    auto pClipboard = glfwGetClipboardString(mGlfwWindow);
    return pClipboard ? pClipboard : std::string();
}

void Window::set_clipboard(const std::string& clipboard)
{
    glfwSetClipboardString(mGlfwWindow, clipboard.c_str());
}

void Window::set_name(const std::string& name)
{
    mName = name;
    mInfo.pName = mName.c_str();
    glfwSetWindowTitle(mGlfwWindow, mName.c_str());
}

void Window::set_cursor_mode(CursorMode cursorMode)
{
    mInfo.cursorMode = cursorMode;
    auto glfwCursorMode = GLFW_CURSOR_NORMAL;
    switch (mInfo.cursorMode) {
    case CursorMode::Visible: glfwCursorMode = GLFW_CURSOR_NORMAL; break;
    case CursorMode::Hidden: glfwCursorMode = GLFW_CURSOR_HIDDEN; break;
    case CursorMode::Disabled: glfwCursorMode = GLFW_CURSOR_DISABLED; break;
    default: assert(false); break;
    }
    glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, glfwCursorMode);
}

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED
void Window::make_context_current()
{
    if (mInfo.graphicsApi == GraphicsApi::OpenGL) {
        glfwMakeContextCurrent(mGlfwWindow);
    }
}

void Window::swap()
{
    if (mInfo.graphicsApi == GraphicsApi::OpenGL) {
        glfwSwapBuffers(mGlfwWindow);
    }
}
#endif // DYNAMIC_STATIC_OPENGL_ENABLED

void Window::poll_events()
{
    access_glfw_windows(
        [](const auto& glfwWindows)
        {
            for (auto pGlfwWindow : glfwWindows) {
                auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
                assert(pDstWindow);
                pDstWindow->mTextStream.clear();
            }
            glfwPollEvents();
            for (auto pGlfwWindow : glfwWindows) {
                auto pDstWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
                assert(pDstWindow);
                pDstWindow->mInput.update();
            }
        }
    );
}

} // namespace sys
} // namespace dst
