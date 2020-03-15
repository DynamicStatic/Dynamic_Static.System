
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#ifndef DYNAMIC_STATIC_OPENGL_DISABLED
#ifndef DYNAMIC_STATIC_OPENGL_ENABLED
#define DYNAMIC_STATIC_OPENGL_ENABLED
#endif
#endif

#ifndef DYNAMIC_STATIC_VULKAN_DISABLED
#ifndef DYNAMIC_STATIC_VULKAN_ENABLED
#define DYNAMIC_STATIC_VULKAN_ENABLED
#endif
#endif

#define DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR 2
#define DYNAMIC_STATIC_SYSTEM_VERSION_MINOR 0
#define DYNAMIC_STATIC_SYSTEM_VERSION_PATCH 0

namespace dst {
namespace sys {

static constexpr int VersionMajor { DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR }; //!< Dynamic_Static.System major version
static constexpr int VersionMinor { DYNAMIC_STATIC_SYSTEM_VERSION_MINOR }; //!< Dynamic_Static.System minor version
static constexpr int VersionPatch { DYNAMIC_STATIC_SYSTEM_VERSION_PATCH }; //!< Dynamic_Static.System patch version

/*!
Specifies system graphics apis.
*/
enum class GraphicsApi
{
    Undefined,
    #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
    OpenGL,
    #endif
    #ifdef DYNAMIC_STATIC_VULKAN_ENABLED
    Vulkan,
    #endif
};

} // namespace sys
} // namespace dst
