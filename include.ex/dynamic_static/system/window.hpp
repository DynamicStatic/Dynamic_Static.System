
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/core/callback.hpp"
#include "dynamic_static/system/defines.hpp"
#ifdef DYNAMIC_STATIC_OPENGL_ENABLED
#include "dynamic_static/system/opengl/defines.hpp"
#endif

#include <string>
#include <vector>

namespace dst {
namespace sys {

/**
TODO : Documentation
*/
class Window final
{
public:
    /**
    TODO : Documentation
    */
    enum class CursorMode
    {
        Visible,  // TOOD : Documentation
        Hidden,   // TOOD : Documentation
        Disabled, // TOOD : Documentation
    };

    /**
    TODO : Documentation
    */
    struct CreateInfo final
    {
        /**
        TODO : Documentation
        */
        enum class Flags
        {
            Decorated  = 1,                  //!< TODO : Documentation
            Resizable  = 1 << 1,             //!< TODO : Documentation
            Visible    = 1 << 2,             //!< TODO : Documentation
            Fullscreen = 1 << 3,             //!< TODO : Documentation
            Default    = Visible | Resizable //!< TODO : Documentation
        };

        Flags flags { Flags::Default };                     //!< TODO : Documentation
        const char* pName { "Dynamic_Static" };             //!< TODO : Documentation
        glm::ivec2 position { 320, 180 };                   //!< TODO : Documentation
        glm::ivec2 resolution { 1280, 720 };                //!< TODO : Documentation
        GraphicsApi graphicsApi { GraphicsApi::Undefined }; //!< TODO : Documentation
        #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
        gl::Context::Info glContextCreateInfo { };    //!< TODO : Documentation
        #endif
    };

    /**
    Constructs an instance of Window
    @param [in] createInfo This Window object's Window::CreateInfo
    */
    Window(const CreateInfo& createInfo);

    /*!
    Moves this instance of Window
    @param [in] other The Window to move from
    */
    Window(Window&& other);

    /*!
    Destroys this instance of Winodw
    */
    ~Window();

    /*!
    Moves this instance of Window
    @param [in] other The Window to move from
    @return A reference to this Window
    */
    Window& operator=(Window&& other);

    /**
    TODO : Documentation
    */
    Callback<Window, const Window&> on_resize;

    /**
    TODO : Documentation
    */
    Callback<Window, const Window&> on_close_requested;

    #ifdef DYNAMIC_STATIC_WINDOWS
    /**
    TODO : Documentation
    */
    void* get_hwnd() const;
    #endif // DYNAMIC_STATIC_WINDOWS

    #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
    /**
    TODO : Documentation
    */
    void make_context_current();

    /**
    TODO : Documentation
    */
    void swap();
    #endif // DYNAMIC_STATIC_OPENGL_ENABLED

    /**
    TODO : Documentation
    */
    static void poll_events();

private:
    std::vector<uint32_t> mTextStream;
    std::string mName { "Dynamic_Static" };
    GraphicsApi mGraphicsApi { GraphicsApi::Undefined };
    void* mWindowHandle { nullptr };
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
};

} // namespace sys
} // namespace dst
