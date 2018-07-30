
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

#include <string>
#include <string_view>
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
        * Configuration parameters for Window construction.
        */
        class Info final
        {
        public:
            GraphicsApi graphicsApi { GraphicsApi::Unknown }; /*!< The configured Window's GraphicsApi */
            std::string name { "Dynamic_Static" };            /*!< The configured Window's name */
            CursorMode cursorMode { CursorMode::Visible };    /*!< The configured Window's CursorMode */
            Resolution resolution { 1280, 720 };              /*!< The configured Window's Resolution */
            glm::vec2 position { 320, 180 };                  /*!< The configured Window's position */
            bool decorated { true };                          /*!< Whether or not the configured Window has decorations (hint) */
            bool resizable { true };                          /*!< Whether or not the configured Window is resizable */
            bool visible { true };                            /*!< Whether or not the configured Window is visiable */
            bool fullScreen { false };                        /*!< Whether or not the configured Window is full screen */

            #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
            /*
            * The configured Window's OpenGL context info
            * \n NOTE : This member is ignored if this Info's graphicsApi member isn't set to OpenGL
            * \n NOTE : This member is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
            */
            gl::ContextInfo glContextInfo { };
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
        std::string mName { "Dynamic_Static" };
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
        * Gets this Window's text stream.
        * @return This Window's text stream
        */
        inline const std::vector<uint32_t>& get_text_stream() const
        {
            return mTextStream;
        }

        /*
        * Gets this Window's name.
        * @return This Window's name
        */
        virtual const std::string& get_name() const
        {
            return mName;
        }

        /*
        * Sets this Window's name.
        * @param [in] name This Window's name
        */
        virtual void set_name(const std::string_view& name) = 0;

        /*
        * Gets this Window's CursorMode.
        * @return This Window's CursorMode
        */
        virtual CursorMode get_cursor_mode() const = 0;

        /*
        * Sets this Window's CursorMode.
        * @param [in] cursorMode This Window's CursorMode
        */
        virtual void set_cursor_mode(CursorMode cursorMode) = 0;

        /*
        * Gets this Window's clipboard.
        * @return This Window's clipboard
        */
        virtual std::string get_clipboard() const = 0;

        /*
        * Sets this Window's clipboard.
        * @param [in] This Window's clipboard
        */
        virtual void set_clipboard(const std::string_view& clipboard) = 0;

        /*
        * Gets a value indicating whether or not this Window is visible.
        * @return Whether or not this Window is visible
        */
        virtual bool is_visible() const = 0;

        /*
        * Sets a value indicating whether or not this Window is visible.
        * @param [in] isVisible Whether or not this Window is visible
        */
        virtual void is_visible(bool isVisible) = 0;

        /*
        * Gets this Window's Resolution.
        * @return This Window's Resolution
        */
        virtual Resolution get_resolution() const = 0;

        #if defined(DYNAMIC_STATIC_WINDOWS)
        /*
        * Gets this Window's HWND.
        * @return This Window's HWND
        * \n NOTE : This method is only available on Windows
        */
        virtual HWND get_hwnd() const = 0;
        #endif

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        /*
        * Makes this Window's OpenGL context current.
        * \n NOTE : This method is a noop if this Window's GraphicsApi isn't OpenGL
        * \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
        */
        virtual void make_context_current() = 0;

        /*
        * Swaps this Window's front and back buffers.
        * \n NOTE : If using OpenGL this method must be called periodically to keep this Window up to date
        * \n NOTE : This method is only available when Dynamic_Static.System is built with DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
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
