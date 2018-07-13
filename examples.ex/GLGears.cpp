
/*
===================================================================================
    Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
    BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
===================================================================================
*/

/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Math/Colors.hpp"
#include "Dynamic_Static/System/OpenGL.hpp"
#include "Dynamic_Static/System/SDL.hpp"
#include "Dynamic_Static/System/Window.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window* window = SDL_CreateWindow(
        "Dynamic_Static",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    static bool sGlewInitialized;
    if (!sGlewInitialized) {
        sGlewInitialized = true;
        glewExperimental = true;
        auto error = glewInit();
        assert(!error);
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:running = false; break;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: running = false; break;
                    }
                } break;
                default:break;
            }
        }

        if (running) {
            int w, h;
            int displayW, displayH;
            SDL_GetWindowSize(window, &w, &h);
            SDL_GL_GetDrawableSize(window, &displayW, &displayH);

            static Uint64 frequency = SDL_GetPerformanceFrequency();
            Uint64 currentTime = SDL_GetPerformanceCounter();

            float r = dst::Color::QuarterGray.r;
            float g = dst::Color::QuarterGray.g;
            float b = dst::Color::QuarterGray.b;
            float a = dst::Color::QuarterGray.a;
            dst_gl(glViewport(0, 0, w, h));
            dst_gl(glClearColor(r, g, b, a));
            dst_gl(glClear(GL_COLOR_BUFFER_BIT));

            SDL_GL_SwapWindow(window);
        }
    }

    #if 0
    using namespace dst::sys;
    Window::Info windowInfo {};
    windowInfo.api = GraphicsApi::OpenGL;
    windowInfo.apiVersion = { 4, 0 };
    Window window(windowInfo);
    std::cout << "hello sys" << std::endl;

    GLuint buffer = 0;
    dst_gl(glCreateBuffers(1, &buffer));
    dst_gl(glDeleteBuffers(1, &buffer));

    bool hit = true;
    while (hit) {
        Window::poll_events();
        window.swap_buffers();
    }
    #endif

    return 0;
}
