
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static.Core.hpp"

#if !defined(DYNAMIC_STATIC_DISABLE_GLFW_SUPPORT)
    #define DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
#endif

#if !defined(DYNAMIC_STATIC_OPENGL_DISABLED)
    #define DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#endif

#if !defined(DYNAMIC_STATIC_VULKAN_DISABLED)
    #define DYNAMIC_STATIC_SYSTEM_VULKAN_ENABLED
#endif

#define DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR 1
#define DYNAMIC_STATIC_SYSTEM_VERSION_MINOR 0
#define DYNAMIC_STATIC_SYSTEM_VERSION_PATCH 0

namespace Dynamic_Static {
namespace System {

    static constexpr int VersionMajor { DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR }; /*!< Dynamic_Static.System major version */
    static constexpr int VersionMinor { DYNAMIC_STATIC_SYSTEM_VERSION_MINOR }; /*!< Dynamic_Static.System minor version */
    static constexpr int VersionPatch { DYNAMIC_STATIC_SYSTEM_VERSION_PATCH }; /*!< Dynamic_Static.System patch version */

    enum class GraphicsApi
    {
        Unknown,

        #if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)
        OpenGL,
        #endif

        #if defined(DYNAMIC_STATIC_SYSTEM_VULKAN_ENABLED)
        Vulkan,
        #endif
    };

} // namespace System
namespace sys = System;
} // namespace Dynamic_Static
