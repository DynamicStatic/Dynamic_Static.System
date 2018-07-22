
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
        */
        inline SDLWindow(const Window::Info& windowInfo)
        {
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
                        mSdlWindow = SDL_CreateWindow(
                            windowInfo.name.c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            windowInfo.resolution.width,
                            windowInfo.resolution.height,
                            flags
                        );
                        if (!mSdlWindow) {
                            std::string errorStr = SDL_GetError();
                            throw std::runtime_error("Failed to create SDL Window : " + errorStr);
                        }
                        sdlWindows.insert(mSdlWindow);
                        SDL_SetWindowData(mSdlWindow, DYNAMIC_STATIC, this);

                        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                        if (windowInfo.graphicsApi == GraphicsApi::OpenGL) {
                            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
                            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, windowInfo.openGlContextInfo.doubleBuffer ? 1 : 0);
                            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, windowInfo.openGlContextInfo.depthBits);
                            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, windowInfo.openGlContextInfo.stencilBits);
                            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, windowInfo.openGlContextInfo.version.major);
                            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, windowInfo.openGlContextInfo.version.minor);
                            mSdlGlContext = SDL_GL_CreateContext(mSdlWindow);
                            if (!mSdlGlContext) {
                                std::string errorStr = SDL_GetError();
                                throw std::runtime_error("Failed to create OpenGL context : " + errorStr);
                            }
                            dst_sdl(SDL_GL_SetSwapInterval(windowInfo.openGlContextInfo.vSync ? 1 : 0));
                            #if defined(DYNAMIC_STATIC_WINDOWS)
                            initialize_glew();
                            #endif
                        }
                        #endif
                    }
                }
            );
        }

        /*
        */
        inline SDLWindow(SDLWindow&& other)
        {
            *this = std::move(other);
        }

        /*
        */
        inline ~SDLWindow()
        {
            access_global_sdl_windows(
                [&](std::set<SDL_Window*>& sdlWindows)
                {
                    #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                    if (mSdlGlContext) {
                        SDL_GL_DeleteContext(mSdlGlContext);
                    }
                    #endif

                    if (mSdlWindow) {
                        SDL_DestroyWindow(mSdlWindow);
                    }
                    sdlWindows.erase(mSdlWindow);
                    if (sdlWindows.empty()) {
                        SDL_Quit();
                    }
                }
            );
        }

        /*
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
        */
        inline Resolution get_resolution() const override final
        {
            int width, height;
            SDL_GetWindowSize(mSdlWindow, &width, &height);
            return { width, height };
        }

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        */
        inline void swap() override final
        {
            SDL_GL_SwapWindow(mSdlWindow);
        }
        #endif

        /*
        */
        static inline void poll_events()
        {
            access_global_sdl_windows(
                [](std::set<SDL_Window*>& sdlWindows) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                            case SDL_KEYDOWN:
                            {
                                auto sdlWindow = SDL_GetWindowFromID(event.key.windowID);
                                auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC));
                                auto dstKey = static_cast<size_t>(detail::sdl_to_dst_key(event.key.keysym.scancode));
                                dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_DOWN;
                            } break;

                            case SDL_KEYUP:
                            {
                                auto sdlWindow = SDL_GetWindowFromID(event.key.windowID);
                                auto dstWindow = reinterpret_cast<SDLWindow*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC));
                                auto dstKey = static_cast<size_t>(detail::sdl_to_dst_key(event.key.keysym.scancode));
                                dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_UP;
                            } break;
                        }
                    }
                    for (auto& sdlWindow : sdlWindows) {
                        reinterpret_cast<SDLWindow*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC))->mInput.update();
                    }
                }
            );
        }

    private:
        static inline Delegate<>& get_poll_events_delegate()
        {

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
    };

} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)

  // SDL_Event event;
  // while (SDL_PollEvent(&event)) {
  //     switch (event.type) {
  //         case SDL_QUIT:running = false; break;
  //         case SDL_KEYDOWN:
  //         {
  //             switch (event.key.keysym.sym) {
  //                 case SDLK_ESCAPE: running = false; break;
  //             }
  //         } break;
  //         default:break;
  //     }
  // }
