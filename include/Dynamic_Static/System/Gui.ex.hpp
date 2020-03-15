#if 0
/*
==========================================
  Copyright (c) 2017-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Window.hpp"

#include "imgui.h"

#include <array>
#include <memory>
#include <string>

namespace dst {
namespace sys {

    /*!
    Provides high level control over rendering an ImGui graphical user interface
    */
    class Gui final
        : NonCopyable
    {
    public:
        /*!
        Provides a common interface for Gui renderers
        */
        class Renderer
        {
            friend class Gui;

        public:
            /*!
            Destroys this instance of Gui::Renderer
            */
            virtual ~Renderer() = 0;

        private:
            /*!
            Draws this Gui::Renderer to the Window passed in Gui::update()
            */
            virtual void draw() = 0;
        };

    private:
        std::unique_ptr<Renderer> mRenderer;

    public:
        /*!
        Constructs an instance of Gui
        @param [in] renderer The Gui::Renderer to use with this Gui
        \n NOTE : This Gui will take ownership of the Gui::Renderer
        */
        Gui(std::unique_ptr<Renderer>&& renderer);

    public:
        /*!
        TODO : Documentation
        @param [in] clock The clock used to maintain update and drawing timing
        @param [in] window The Window associated with this Gui
        */
        void begin_frame(
            const Clock& clock,
            Window& window
        );

        /*!
        TODO : Documentation
        */
        void end_frame();

        /*!
        Draws this Gui to the Window passed in update()
        */
        void draw();

    private:
        static const char* get_clipboard(void* userData);
        static void set_clipboard(void* userData, const char* clipboard);
    };

} // namespace sys
} // namespace dst
#endif