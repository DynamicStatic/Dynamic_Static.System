
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core.Ex/Defines.hpp"

#ifndef DYNAMIC_STATIC_OPENGL_DISABLED
#define DYNAMIC_STATIC_OPENGL_ENABLED 1
#endif

#ifndef DYNAMIC_STATIC_VULKAN_DISABLED
#define DYNAMIC_STATIC_VULKAN_ENABLED 1
#endif

#define DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR 1
#define DYNAMIC_STATIC_SYSTEM_VERSION_MINOR 0
#define DYNAMIC_STATIC_SYSTEM_VERSION_PATCH 0

namespace Dynamic_Static {
namespace System {

    static constexpr int VersionMajor { DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR }; /*!< TODO : Documentation. */
    static constexpr int VersionMinor { DYNAMIC_STATIC_SYSTEM_VERSION_MINOR }; /*!< TODO : Documentation. */
    static constexpr int VersionPatch { DYNAMIC_STATIC_SYSTEM_VERSION_PATCH }; /*!< TODO : Documentation. */

    enum class GraphicsApi
    {
        Unknonwn, /*!< TODO : Documentation. */

        #if DYNAMIC_STATIC_OPENGL_ENABLED
        OpenGL, /*!< TODO : Documentation. */
        #endif

        #if DYNAMIC_STATIC_VULKAN_ENABLED
        Vulkan, /*!< TODO : Documentation. */
        #endif
    };

} // namespace System
    namespace sys = System;
} // namespace Dynamic_Static
