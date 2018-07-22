
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)

#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
#include "Dynamic_Static/System/OpenGL.hpp"
#endif

#define HAVE_M_PI
#include "SDL/SDL.h"

#define DYNAMIC_STATIC_VALIDATE_SDL_CALLS
#if defined(DYNAMIC_STATIC_VALIDATE_SDL_CALLS)
#define dst_sdl(SDL_CALL)                                                 \
{                                                                         \
    auto sdlError = SDL_CALL;                                             \
    dst::sys::validate_last_sdl_call(sdlError, dst_file_line, #SDL_CALL); \
}
#else
#define dst_sdl(SDL_CALL) \
{                         \
    SDL_CALL;             \
}
#endif

namespace Dynamic_Static {
namespace System {

    /*
    * TODO : Documentation.
    */
    inline int validate_last_sdl_call(int sdlError, const char* message, const char* sdlCall)
    {
        // TODO : Set up proper logging mechanism...
        // TODO : Configurre SDL log integration...
        if (sdlError) {
            auto errorStr = SDL_GetError();
            if (!errorStr) {
                errorStr = "Unknown";
            }
            std::cerr
                << "SDL Error [" << sdlError << ":" << errorStr << "]\n"
                << "    " << message << "\n"
                << "    " << sdlCall << "\n"
                << std::endl;
        }
        return sdlError;
    }

} // namespace Dynamic_Static
} // namespace System

#endif // defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)
