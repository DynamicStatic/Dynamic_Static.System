
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

#if defined(DYNAMIC_STATIC_GLFW_ENABLED)
#include "Dynamic_Static/System/GLFW.hpp"
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
            #endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        };

    public:
        /*
        * Callback executed when this Window is resized.
        * @param [in] The Window being resized
        */
        Callback<Window, const Window&> on_resized;

    public:
        /*
        * Constructs an instance of Window.
        * @param [in] info This Window's Window::Info
        */
        inline Window(const Info& info);

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        */
        inline Window(Window&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of Winodw.
        */
        inline ~Window();

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        * @return This Window
        */
        inline Window& operator=(Window&& other);

    private:
        #if defined(DYNAMIC_STATIC_SDL_ENABLED)
        DYNAMIC_STATIC_SDL_WINDOW_MEMBERS
        #endif
        std::vector<uint32_t> mTextStream;
        Input mInput;

    public:
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
        * @return This Window's Resolution
        */
        inline Resolution get_resolution() const;

        #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
        /*
        * TODO : Documentation.
        */
        inline void swap();
        #endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)

        /*
        * TODO : Documentation.
        */
        static inline void poll_events();
    };

} // namespace System
} // namespace Dynamic_Static

#if defined(DYNAMIC_STATIC_GLFW_ENABLED)
#include "Dynamic_Static/System/Window/Window.GLFW.inl"
#endif

#if defined(DYNAMIC_STATIC_SDL_ENABLED)
#include "Dynamic_Static/System/Window/Window.SDL.inl"
#endif
