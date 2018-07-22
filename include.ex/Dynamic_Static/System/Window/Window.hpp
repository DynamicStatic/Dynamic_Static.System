
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
#include "Dynamic_Static/Core/Events.hpp"
#include "Dynamic_Static/Core/Math.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Resolution.hpp"

#if defined(DYNAMIC_STATIC_SYSTEM_SDL_ENABLED)
#include "Dynamic_Static/System/SDL.hpp"
#endif

#include <memory>
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
    class Window
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

            #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
            /*
            * The configured Window's OpenGL context
            * \n NOTE : This member is ignored if this Info's graphicsApi member isn't set to OpenGL
            */
            OpenGLContextInfo openGlContextInfo { };
            #endif
        };

    public:
        /*
        * Callback executed when this Window is resized.
        * @param [in] The Window being resized
        */
        Callback<Window, const Window&> on_resize;

    protected:
        Input mInput;
        std::vector<uint32_t> mTextStream;
        GraphicsApi mGraphicsApi { GraphicsApi::Unknown };

    public:
        /*
        * Constructs an instance of Window.
        */
        inline Window() = default;

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
        virtual inline ~Window() = 0;

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        * @return This Window
        */
        virtual inline Window& operator=(Window&& other)
        {
            if (this != &other) {
                mInput = std::move(other.mInput);
                mTextStream = std::move(other.mTextStream);
                mGraphicsApi = std::move(other.mGraphicsApi);
            }
            return *this;
        }

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
        virtual Resolution get_resolution() const = 0;

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        * TODO : Documentation.
        */
        virtual void swap() = 0;
        #endif

        /*
        * TODO : Documentation.
        */
        static inline void poll_events()
        {
            get_poll_events_event()();
        }

    protected:
        static inline Event<Window>& get_poll_events_event()
        {
            static Event<Window> sOnPollEvents;
            return sOnPollEvents;
        }
    };

    Window::~Window()
    {
    }

} // namespace System
} // namespace Dynamic_Static
