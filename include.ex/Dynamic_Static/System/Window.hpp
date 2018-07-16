
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Callback.hpp"
#include "Dynamic_Static/Core/Math.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Resolution.hpp"

#if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
#include "Dynamic_Static/System/OpenGL.hpp"
#endif

#if defined(DYNAMIC_STATIC_SDL_ENABLED)
#include "Dynamic_Static/System/SDL.hpp"
#endif

#include <mutex>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over a system window.
    */
    class Window final
        : NonCopyable
    {
    public:
        /*
        * Specifies cursor modes.
        */
        enum class CursorMode
        {
            Visible,
            Hidden,
            Disabled,
        };

        /*
        * Specifies configuration parameters for Window construction.
        */
        class Info final
        {
        public:
            GraphicsApi graphicsApi { GraphicsApi::Unknown };   /*!< The configured Window's GraphicsApi */
            std::string name { "Dynamic_Static" };              /*!< The configured Window's name */
            CursorMode cursorMode { CursorMode::Visible };      /*!< The configured Window's CursorMode */
            Resolution resolution { 1280, 720 };                /*!< The configured Window's Resolution */
            glm::vec2 position { 320, 180 };                    /*!< The configured Window's position */
            bool decorated { true };                            /*!< Whether or not the configured Window has decorations (hint) */
            bool resizable { true };                            /*!< Whether or not the configured Window is resizable */
            bool visible { true };                              /*!< Whether or not the configured Window is visiable */
            bool fullScreen { false };                          /*!< Whether or not the configured Window is full screen */
            Window* parent { nullptr };                         /*!< The configured Window's parent Window */

            #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
            /*
            * The configured Window's OpenGL context
            * \n NOTE : This member is ignored if this Info's graphicsApi member isn't set to OpenGL
            */
            OpenGLContextInfo openGlContextInfo { };
            #endif
        };

    private:
        #if defined(DYNAMIC_STATIC_SDL_ENABLED)
        SDL_Window* mHandle { nullptr };
        SDL_GLContext mGlContext { nullptr };
        #endif

        std::vector<uint32_t> mTextStream;
        Input mInput;

    public:
        /*
        * Callback executed when this Window is resized.
        * @param [in] The Window being resized
        */
        Callback<Window, const Window&> on_resized;

    public:
        /*
        * Constructs an instance of Window.
        * @param [in] configuration This Window's Configuration (optional = default Configuration)
        */
        inline Window(const Info& configuration);

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        */
        inline Window(Window&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of Window.
        */
        inline ~Window();

        /*
        * Moves an instance of Window.
        * @param [in] other The Window to move from
        */
        inline Window& Window::operator=(Window&& other)
        {
            if (this != &other) {
                mHandle = std::move(other.mHandle);
                mTextStream = std::move(other.mTextStream);
                mInput = std::move(other.mInput);
                other.mHandle = nullptr;
            }
            return *this;
        }

    public:
        #if defined(DYNAMIC_STATIC_SDL_ENABLED)
        /*
        * Gets this Window's SDL_Window handle.
        * @return This Window's SDL_Window handle
        */
        inline SDL_Window* get_handle() const
        {
            return mHandle;
        }

        #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        /*
        * Gets this Window's SDL_GLContext.
        * @return This Window's SDL_GLContext
        */
        inline SDL_GLContext get_gl_context() const
        {
            return mGlContext;
        }
        #endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        #endif // defined(DYNAMIC_STATIC_SDL_ENABLED)

        /*
        * Gets this Window's Input.
        * @return This Window's Input
        */
        inline const Input& get_input() const
        {
            return mInput;
        }

        /*
        * Gets this Window's Resolution.
        * @return This Window'w Resolution
        */
        inline Resolution get_resolution() const;

        #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        /*
        * TODO : Documentation.
        */
        inline void swap();
        #endif // DYNAMIC_STATIC_OPENGL_ENABLED
    };

} // namespace System
} // namespace Dynamic_Static

#if defined(DYNAMIC_STATIC_SDL_ENABLED)
namespace Dynamic_Static {
namespace System {
namespace detail {

    template <typename FunctionType>
    inline void manipulate_global_sdl_window_set(FunctionType f)
    {
        static std::mutex sMutex;
        static std::set<SDL_Window*> sSdlWindows;
        std::lock_guard<std::mutex> lock(sMutex);
        f(sSdlWindows);
    }

} // namespace detail

    inline Window::Window(const Info& info)
    {
        #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        if (info.graphicsApi == GraphicsApi::OpenGL) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, info.openGlContextInfo.doubleBuffer ? 1 : 0);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, info.openGlContextInfo.depthBits);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, info.openGlContextInfo.stencilBits);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, info.openGlContextInfo.version.major);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, info.openGlContextInfo.version.minor);
            SDL_DisplayMode current { };
            SDL_GetCurrentDisplayMode(0, &current);
            Uint32 flags = SDL_WINDOW_OPENGL;
            if (info.resizable) {
                flags |= SDL_WINDOW_RESIZABLE;
            }
            mHandle = SDL_CreateWindow(
                info.name.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                info.resolution.width,
                info.resolution.height,
                flags
            );
            if (!mHandle) {
                auto sdlErrorCStr = SDL_GetError();
                std::string sdlErrorStr = sdlErrorCStr ? sdlErrorCStr : "Unknown";
                throw std::runtime_error("Failed to create SDL Window:" + sdlErrorStr);
            }
            mGlContext = SDL_GL_CreateContext(mHandle);
            if (!mGlContext) {
                auto sdlErrorCStr = SDL_GetError();
                std::string sdlErrorStr = sdlErrorCStr ? sdlErrorCStr : "Unknown";
                throw std::runtime_error("Failed to create OpenGL context:" + sdlErrorStr);
            }
            dst_sdl(SDL_GL_SetSwapInterval(info.openGlContextInfo.vSync ? 1 : 0));
            initialize_glew();
        }
        #endif // DYNAMIC_STATIC_OPENGL_ENABLED
    }

    inline Window::~Window()
    {
    }

    inline Resolution Window::get_resolution() const
    {
        int width, height;
        SDL_GetWindowSize(mHandle, &width, &height);
        return { width, height };
    }

    #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
    inline void Window::swap()
    {
        SDL_GL_SwapWindow(mHandle);
    }
    #endif // DYNAMIC_STATIC_OPENGL_ENABLED

} // namespace System
} // namespace Dynamic_Static
#endif // defined(DYNAMIC_STATIC_SDL_ENABLED)
