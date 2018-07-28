
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include "fmod.hpp"

namespace Dynamic_Static {
namespace System {

    void fmod_audio_test()
    {
        FMOD::System* system = nullptr;
        auto fmResult = FMOD::System_Create(&system);
        if (fmResult != FMOD_OK) {
            assert(false);
        }
        fmResult = system->init(512, FMOD_INIT_NORMAL, 0);
        if (fmResult != FMOD_OK) {
            assert(false);
        }
    }

} // namespace System
} // namespace Dynamic_Static
