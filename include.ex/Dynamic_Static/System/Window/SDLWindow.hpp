
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#if defined(DYNAMIC_STATIC_SDL_ENABLED)

namespace Dynamic_Static {
namespace System {
namespace detail {

    inline void access_global_sdl_windows(
        const std::function<void(std::set<SDL_Window*>&)>& accessFunction
    )
    {
        static std::mutex sMutex;
        static std::set<SDL_Window*> sSdlWindows;
        std::lock_guard<std::mutex> lock(sMutex);
        accessFunction(sSdlWindows);
    }

} // namespace detail

    inline Window::Window(const Info& info)
    {
        detail::access_global_sdl_windows(
            [&](std::set<SDL_Window*>& sdlWindows)
            {
                if (sdlWindows.empty()) {
                    auto error = SDL_Init(SDL_INIT_VIDEO);
                    if (error) {
                        std::string errorStr = SDL_GetError();
                        throw std::runtime_error("Failed to initialize SDL : " + errorStr);
                    }

                    Uint32 flags = 0;
                    flags |= info.resizable ? SDL_WINDOW_RESIZABLE : 0;
                    #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                    flags |= info.graphicsApi == GraphicsApi::OpenGL ? SDL_WINDOW_OPENGL : 0;
                    #endif
                    mSdlWindow = SDL_CreateWindow(
                        info.name.c_str(),
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        info.resolution.width,
                        info.resolution.height,
                        flags
                    );
                    if (!mSdlWindow) {
                        std::string errorStr = SDL_GetError();
                        throw std::runtime_error("Failed to create SDL Window : " + errorStr);
                    }
                    sdlWindows.insert(mSdlWindow);
                    SDL_SetWindowData(mSdlWindow, DYNAMIC_STATIC, this);

                    #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
                    if (info.graphicsApi == GraphicsApi::OpenGL) {
                        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
                        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, info.openGlContextInfo.doubleBuffer ? 1 : 0);
                        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, info.openGlContextInfo.depthBits);
                        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, info.openGlContextInfo.stencilBits);
                        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, info.openGlContextInfo.version.major);
                        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, info.openGlContextInfo.version.minor);
                        mSdlGlContext = SDL_GL_CreateContext(mSdlWindow);
                        if (!mSdlGlContext) {
                            std::string errorStr = SDL_GetError();
                            throw std::runtime_error("Failed to create OpenGL context : " + errorStr);
                        }
                        dst_sdl(SDL_GL_SetSwapInterval(info.openGlContextInfo.vSync ? 1 : 0));
                        #if defined(DYNAMIC_STATIC_WINDOWS)
                        initialize_glew();
                        #endif
                    }
                    #endif
                }
            }
        );
    }

    inline Window::~Window()
    {
        detail::access_global_sdl_windows(
            [&](std::set<SDL_Window*>& sdlWindows)
            {
                #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
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

    inline Window& Window::operator=(Window&& other)
    {
        if (this != &other) {
            SDL_SetWindowData(mSdlWindow, DYNAMIC_STATIC, this);
            mSdlWindow = std::move(other.mSdlWindow);
            mSdlGlContext = std::move(other.mSdlGlContext);
            mTextStream = std::move(other.mTextStream);
            mInput = std::move(other.mInput);
            other.mSdlWindow = nullptr;
            other.mSdlGlContext = nullptr;
        }
        return *this;
    }

    inline Resolution Window::get_resolution() const
    {
        int width, height;
        SDL_GetWindowSize(mSdlWindow, &width, &height);
        return { width, height };
    }

    #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
    inline void Window::swap()
    {
        SDL_GL_SwapWindow(mSdlWindow);
    }
    #endif

    inline void Window::poll_events()
    {
        detail::access_global_sdl_windows(
            [](std::set<SDL_Window*>& sdlWindows) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_KEYDOWN:
                        {
                            auto sdlWindow = SDL_GetWindowFromID(event.key.windowID);
                            auto dstWindow = reinterpret_cast<Window*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC));
                            auto dstKey = static_cast<size_t>(detail::sdl_to_dst_key(event.key.keysym.scancode));
                            dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_DOWN;
                        } break;

                        case SDL_KEYUP:
                        {
                            auto sdlWindow = SDL_GetWindowFromID(event.key.windowID);
                            auto dstWindow = reinterpret_cast<Window*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC));
                            auto dstKey = static_cast<size_t>(detail::sdl_to_dst_key(event.key.keysym.scancode));
                            dstWindow->mInput.keyboard.staged[dstKey] = DST_KEY_UP;
                        } break;
                    }
                }

                for (auto& sdlWindow : sdlWindows) {
                    reinterpret_cast<Window*>(SDL_GetWindowData(sdlWindow, DYNAMIC_STATIC))->mInput.update();
                }
            }
        );
    }

} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_SDL_ENABLED)
