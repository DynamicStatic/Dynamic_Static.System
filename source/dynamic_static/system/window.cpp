
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
    , mName { info.pName ? info.pName : "Dynamic_Static" }
{
    mInfo.pName = mName.c_str();
    mGlfwWindow = create_glfw_window(info);
    if (mGlfwWindow) {
        glfwSetWindowUserPointer(mGlfwWindow, this);
        glfwGetFramebufferSize(mGlfwWindow, &mInfo.extent.x, &mInfo.extent.y);
    }
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
    mChildren = std::move(other.mChildren);
    other.mGlfwWindow = nullptr;
    glfwSetWindowUserPointer(mGlfwWindow, this);
    return *this;
}

const Window::Info& Window::get_info() const
{
    return mInfo;
}

const Window* Window::get_parent() const
{
    return (const Window*)glfwGetWindowUserPointer(mParentGlfwWindow);
}

Window* Window::get_parent()
{
    return (Window*)glfwGetWindowUserPointer(mParentGlfwWindow);
}

dst::Span<const Window> Window::get_children() const
{
    return mChildren;
}

dst::Span<Window> Window::get_children()
{
    return mChildren;
}

const Input& Window::get_input() const
{
    return mInput;
}

Input& Window::get_input()
{
    return mInput;
}

dst::Span<const uint32_t> Window::get_text_stream() const
{
    return mTextStream;
}

#ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
void* Window::get_hwnd() const
{
    return glfwGetWin32Window(mGlfwWindow);
}
#endif // DYNAMIC_STATIC_PLATFORM_WINDOWS

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

Window* Window::create_child(const Info& info)
{
    assert(false && "Not yet implemented");
    return nullptr;
}

void Window::focus() const
{
    glfwFocusWindow(mGlfwWindow);
}

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
void Window::make_context_current()
{
    if (mInfo.pGlInfo) {
        glfwMakeContextCurrent(mGlfwWindow);
    }
}

void Window::swap()
{
    if (mInfo.pGlInfo) {
        glfwSwapBuffers(mGlfwWindow);
    }
}
#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

void Window::poll_events()
{
    access_glfw_windows(
        [](const auto& glfwWindows)
        {
            for (auto pGlfwWindow : glfwWindows) {
                auto pWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
                assert(pWindow);
                if (pWindow) {
                    pWindow->mTextStream.clear();
                }
            }
            glfwPollEvents();
            for (auto pGlfwWindow : glfwWindows) {
                auto pWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
                assert(pWindow);
                if (pWindow) {
                    pWindow->mInput.update();
                }
            }
        }
    );
}

} // namespace sys
} // namespace dst
