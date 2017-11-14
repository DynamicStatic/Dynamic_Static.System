
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Time.hpp"
#include "Dynamic_Static/Core/Object.hpp"
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Window.hpp"

#include <memory>
#include <string>

namespace Dynamic_Static {
namespace System {

    /**
     * TODO : Documentation.
     */
    class Application
        : public Object
    {
    protected:
        dst::Clock mClock;
        dst::Version mVersion { 1, 0, 0 };
        Window::Configuration mWindowConfiguration;
        std::shared_ptr<Window> mWindow;
        bool mRunning { false };

    public:
        /**
         * TODO : Documentation.
         */
        virtual ~Application() = 0;

    public:
        /**
         * Gets a value indicating whether or not this Application is running.
         * @return Whether or not this Application is running
         */
        bool running() const;

        /**
         * TODO : Documentation.
         */
        virtual void setup();

        /**
         * TODO : Documentation.
         */
        void start();

        /**
         * TODO : Documentation.
         */
        virtual void pre_update(const dst::Clock& clock, const Input& input);

        /**
         * TODO : Documentation.
         */
        virtual void update(const dst::Clock& clock, const Input& input);

        /**
         * TODO : Documentation.
         */
        virtual void post_update(const dst::Clock& clock, const Input& input);

        /**
         * TODO : Documentation.
         */
        virtual void pre_render(const dst::Clock& clock);

        /**
         * TODO : Documentation.
         */
        virtual void render(const dst::Clock& clock);

        /**
         * TODO : Documentation.
         */
        virtual void post_render(const dst::Clock& clock);

        /**
         * TODO : Documentation.
         */
        virtual void shutdown();

        /**
         * TODO : Documentation.
         */
        void stop();
    };

} // namespace System
} // namespace Dynamic_Static
