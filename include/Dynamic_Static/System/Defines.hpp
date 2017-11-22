
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#ifndef DYNAMIC_STATIC_OPENGL_SUPPORT_DISABLED
    #define DYNAMIC_STATIC_OPENGL_SUPPORTED (1)
#endif

#ifndef DYNAMIC_STATIC_VULKAN_SUPPORT_DISABLED
    #define DYNAMIC_STATIC_VULKAN_SUPPORTED (1)
#endif

#define DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR (0)
#define DYNAMIC_STATIC_SYSTEM_VERSION_MINOR (0)
#define DYNAMIC_STATIC_SYSTEM_VERSION_PATCH (1)

namespace Dynamic_Static {
namespace System {

    enum class API
    {
        Unknown, /*!< TODO : Documentation. */

        #if DYNAMIC_STATIC_OPENGL_SUPPORTED
        OpenGL, /*!< TODO : Documentation. */
        #endif

        #if DYNAMIC_STATIC_VULKAN_SUPPORTED
        Vulkan, /*!< TODO : Documentation. */
        #endif
    };

} // namespace System
namespace sys = System;
} // namespace Dynamic_Static
