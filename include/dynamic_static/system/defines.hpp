
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

#ifndef DYNAMIC_STATIC_SYSTEM_OPENGL_DISABLED
#ifndef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#define DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#endif
#endif

#define DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR 2
#define DYNAMIC_STATIC_SYSTEM_VERSION_MINOR 0
#define DYNAMIC_STATIC_SYSTEM_VERSION_PATCH 0

namespace dst {
namespace sys {

static constexpr int VersionMajor { DYNAMIC_STATIC_SYSTEM_VERSION_MAJOR };
static constexpr int VersionMinor { DYNAMIC_STATIC_SYSTEM_VERSION_MINOR };
static constexpr int VersionPatch { DYNAMIC_STATIC_SYSTEM_VERSION_PATCH };

} // namespace sys
} // namespace dst
