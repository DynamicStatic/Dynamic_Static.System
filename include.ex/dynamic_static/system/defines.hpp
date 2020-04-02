
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

static constexpr int VersionMajor { DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR }; //!< dynamic_static.system major version
static constexpr int VersionMinor { DYNAMIC_STATIC_SYSTEM_VERSION_MINOR }; //!< dynamic_static.system minor version
static constexpr int VersionPatch { DYNAMIC_STATIC_SYSTEM_VERSION_PATCH }; //!< dynamic_static.system patch version

} // namespace sys
} // namespace dst

namespace dst {
namespace gfx {

/*!
Specifies graphics apis
*/
enum class Api
{
    Undefined,
    #ifdef DYNAMIC_STATIC_OPENGL_ENABLED
    OpenGL,
    #endif
    #ifdef DYNAMIC_STATIC_VULKAN_ENABLED
    Vulkan,
    #endif
};

} // namespace gfx
} // namespace dst
