
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)

#include "Dynamic_Static/Core/Events.hpp"
#include "Dynamic_Static/System/Window/Window.hpp"
#include "Dynamic_Static/System/SDL.hpp"

#include <utility>

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over an SDL_Window.
    */
    class SDLWindow final
        : public Window
    {
    private:
        SDL_Window* mSdlWindow { nullptr };
        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        SDL_GLContext mSdlGlContext { nullptr };
        #endif

    public:
        /*
        * Constructs an instance of SDLWindow.
        * @param [in] windowInfo This SDLWindow's Window::Info.
        */
        inline SDLWindow(const Window::Info& windowInfo)
        {
            mGraphicsApi = windowInfo.graphicsApi;
            mSdlWindow = create_sdl_window(windowInfo);
            SDL_SetWindowData(mSdlWindow, DYNAMIC_STATIC, this);
            #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
            if (mGraphicsApi == GraphicsApi::OpenGL) {
                mSdlGlContext = create_sdl_gl_context(mSdlWindow, windowInfo);
            }
            #endif
        }

        /*
        * Moves this instance of SDLWindow.
        * @param [in] other The SDLWindow to move from
        */
        inline SDLWindow(SDLWindow&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of SDLWindow.
        */
        inline ~SDLWindow()
        {
            #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
            if (mSdlGlContext) {
                destroy_sdl_gl_context(mSdlGlContext);
            }
            #endif
            if (mSdlWindow) {
                destroy_sdl_window(mSdlWindow);
            }
        }

        /*
        * Moves this instance of SDLWindow.
        * @param [in] other The SDLWindow to move from
        * @return This SDLWindow
        */
        inline SDLWindow& operator=(SDLWindow&& other)
        {
            if (this != &other) {
                Window::operator=(std::move(other));
                SDL_SetWindowData(mSdlWindow, DYNAMIC_STATIC, this);
                mSdlWindow = std::move(other.mSdlWindow);
                other.mSdlWindow = nullptr;
                #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                mSdlGlContext = std::move(other.mSdlGlContext);
                other.mSdlGlContext = nullptr;
                #endif
            }
            return *this;
        }

    public:
        /*
        * Gets this SDLWindow's Resolution.
        * @return This SDLWindow's Resolution
        */
        inline Resolution get_resolution() const override final
        {
            int width, height;
            SDL_GetWindowSize(mSdlWindow, &width, &height);
            return { width, height };
        }

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        * Swaps this SDLWindow's front and back buffers.
        * \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        * \n NOTE : If using OpenGL this method must be called periodically to keep this SDLWindow up to date
        */
        inline void swap() override final
        {
            if (mGraphicsApi == GraphicsApi::OpenGL) {
                SDL_GL_MakeCurrent(mSdlWindow, mSdlGlContext);
                SDL_GL_SwapWindow(mSdlWindow);
            }
        }
        #endif

        /*
        * Processes pending system events.
        * \n NOTE : This method should be called periodically to keep all SDLWindow up to date
        * \n NOTE : This method is triggered by Window::poll_events(), one or the other should be used, not both
        */
        static inline void poll_events()
        {
            access_global_sdl_windows(
                [&](std::set<SDL_Window*>& sdlWindows) {
                    for (auto& sdlWindow : sdlWindows) {
                        auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC));
                        assert(dstWindow);
                        dstWindow->mTextStream.clear();
                    }

                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                            case SDL_WINDOWEVENT:
                            {
                                switch (event.window.event) {
                                    case SDL_WINDOWEVENT_CLOSE:
                                    {
                                        auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.button.windowID), DYNAMIC_STATIC));
                                        assert(dstWindow);
                                        dstWindow->execute_on_close_callback();
                                    } break;
                                    case SDL_WINDOWEVENT_RESIZED:
                                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                                    {
                                        auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.button.windowID), DYNAMIC_STATIC));
                                        assert(dstWindow);
                                        dstWindow->execute_on_resize_callback();
                                    } break;
                                }
                            } break;
                            case SDL_KEYUP:
                            case SDL_KEYDOWN:
                            {
                                auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.key.windowID), DYNAMIC_STATIC));
                                assert(dstWindow);
                                auto dstKey = static_cast<size_t>(detail::sdl_to_dst_key(event.key.keysym.scancode));
                                dstWindow->mInput.keyboard.staged[dstKey] = event.key.state == SDL_PRESSED ? DST_KEY_DOWN : DST_KEY_UP;
                            } break;
                            case SDL_MOUSEBUTTONUP:
                            case SDL_MOUSEBUTTONDOWN:
                            {
                                auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.button.windowID), DYNAMIC_STATIC));
                                assert(dstWindow);
                                auto dstMouseButton = static_cast<size_t>(detail::sdl_to_dst_mouse_button(event.button.button));
                                dstWindow->mInput.mouse.staged.buttons[dstMouseButton] = event.button.state == SDL_PRESSED ? DST_BUTTON_DOWN : DST_BUTTON_UP;
                            } break;
                            case SDL_MOUSEWHEEL:
                            {
                                auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.wheel.windowID), DYNAMIC_STATIC));
                                assert(dstWindow);
                                dstWindow->mInput.mouse.staged.scroll += static_cast<float>(event.wheel.y);
                            } break;
                        }
                    }

                    int mx, my;
                    SDL_GetGlobalMouseState(&mx, &my);
                    for (auto& sdlWindow : sdlWindows) {
                        int wx, wy;
                        SDL_GetWindowPosition(sdlWindow, &wx, &wy);
                        auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC));
                        assert(dstWindow);
                        dstWindow->mInput.mouse.staged.position = { mx - wx, my - wy };
                        dstWindow->mInput.update();
                    }
                }
            );
        }

    private:
        static inline Delegate<>& get_poll_events_delegate()
        {
            static Delegate<> sOnPollEvents;
            sOnPollEvents = poll_events;
            return sOnPollEvents;
        }

        static inline void access_global_sdl_windows(
            const std::function<void(std::set<SDL_Window*>&)>& accessFunction
        )
        {
            static std::mutex sMutex;
            static std::set<SDL_Window*> sSdlWindows;
            std::lock_guard<std::mutex> lock(sMutex);
            accessFunction(sSdlWindows);
        }

        static inline SDL_Window* create_sdl_window(const Window::Info& windowInfo)
        {
            SDL_Window* sdlWindow = nullptr;
            access_global_sdl_windows(
                [&](std::set<SDL_Window*>& sdlWindows)
                {
                    if (sdlWindows.empty()) {
                        auto error = SDL_Init(SDL_INIT_VIDEO);
                        if (error) {
                            std::string errorStr = SDL_GetError();
                            throw std::runtime_error("Failed to initialize SDL : " + errorStr);
                        }

                        Uint32 flags = 0;
                        flags |= windowInfo.resizable ? SDL_WINDOW_RESIZABLE : 0;
                        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                        flags |= windowInfo.graphicsApi == GraphicsApi::OpenGL ? SDL_WINDOW_OPENGL : 0;
                        #endif
                        sdlWindow = SDL_CreateWindow(
                            windowInfo.name.c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            windowInfo.resolution.width,
                            windowInfo.resolution.height,
                            flags
                        );
                        if (!sdlWindow) {
                            std::string errorStr = SDL_GetError();
                            throw std::runtime_error("Failed to create SDL Window : " + errorStr);
                        }
                        sdlWindows.insert(sdlWindow);
                    }
                }
            );
            return sdlWindow;
        }

        static inline void destroy_sdl_window(SDL_Window* sdlWindow)
        {
            access_global_sdl_windows(
                [&](std::set<SDL_Window*>& sdlWindows)
                {
                    if (sdlWindow) {
                        SDL_DestroyWindow(sdlWindow);
                    }
                    sdlWindows.erase(sdlWindow);
                    if (sdlWindows.empty()) {
                        get_poll_events_event() -= get_poll_events_delegate();
                        SDL_Quit();
                    }
                }
            );
        }

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        static inline SDL_GLContext create_sdl_gl_context(
            SDL_Window* sdlWindow,
            const Window::Info& windowInfo
        )
        {
            SDL_GLContext sdlGlContext = nullptr;
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, windowInfo.openGlContextInfo.doubleBuffer ? 1 : 0);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, windowInfo.openGlContextInfo.depthBits);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, windowInfo.openGlContextInfo.stencilBits);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, windowInfo.openGlContextInfo.version.major);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, windowInfo.openGlContextInfo.version.minor);
            sdlGlContext = SDL_GL_CreateContext(sdlWindow);
            if (!sdlGlContext) {
                std::string errorStr = SDL_GetError();
                throw std::runtime_error("Failed to create OpenGL context : " + errorStr);
            }
            dst_sdl(SDL_GL_SetSwapInterval(windowInfo.openGlContextInfo.vSync ? 1 : 0));
            #if defined(DYNAMIC_STATIC_WINDOWS)
            initialize_glew();
            #endif
            return sdlGlContext;
        }

        static inline void destroy_sdl_gl_context(SDL_GLContext sdlGlContext)
        {
            if (sdlGlContext) {
                SDL_GL_DeleteContext(sdlGlContext);
            }
        }
        #endif
    };

} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)
