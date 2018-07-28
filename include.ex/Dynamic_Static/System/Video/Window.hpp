
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
#include "Dynamic_Static/System/Video/Resolution.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"

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
    class IWindow
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
        Callback<IWindow, const IWindow&> on_resize;

        /*
        * Callback executed when this Window is closed.
        * @param [in] The Window being closed
        */
        Callback<IWindow, const IWindow&> on_close;

    protected:
        Input mInput;
        std::vector<uint32_t> mTextStream;
        GraphicsApi mGraphicsApi { GraphicsApi::Unknown };

    public:
        /*
        * Constructs an instance of Window.
        */
        inline IWindow() = default;

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        */
        inline IWindow(IWindow&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of Winodw.
        */
        virtual inline ~IWindow() = 0;

        /*
        * Moves this instance of Window.
        * @param [in] other The Window to move from
        * @return This Window
        */
        virtual inline IWindow& operator=(IWindow&& other)
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
        * Swaps this Window's front and back buffers.
        * \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        * \n NOTE : If using OpenGL this method must be called periodically to keep this Window up to date
        */
        virtual void swap() = 0;
        #endif

        /*
        * Processes pending system events.
        * \n NOTE : This method should be called periodically to keep all Windows up to date
        * \n NOTE : This method triggers derived implementations of poll_events()
        */
        static inline void poll_events()
        {
            get_poll_events_event()();
        }

    protected:
        inline void execute_on_resize_callback()
        {
            on_resize(*this);
        }

        inline void execute_on_close_callback()
        {
            on_close(*this);
        }

        static inline Event<IWindow>& get_poll_events_event()
        {
            static Event<IWindow> sOnPollEvents;
            return sOnPollEvents;
        }
    };

    IWindow::~IWindow()
    {
    }

} // namespace System
} // namespace Dynamic_Static
