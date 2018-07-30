
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

    FMOD::System* fmod_init()
    {
        FMOD::System* system = nullptr;
        auto fmResult = FMOD::System_Create(&system);
        assert(fmResult == FMOD_OK);

        fmResult = system->init(512, FMOD_INIT_NORMAL, 0);
        assert(fmResult == FMOD_OK);

        FMOD::Sound* sound = nullptr;
        auto filePath = "../../examples/resources/Track_00.ogg";
        fmResult = system->createSound(filePath, FMOD_CREATESTREAM, nullptr, &sound);
        assert(fmResult == FMOD_OK);

        fmResult = system->playSound(sound, nullptr, false, nullptr);
        assert(fmResult == FMOD_OK);

        return system;
    }

    void fmod_update(FMOD::System* system)
    {
        system->update();
    }

    void fmod_shutdown(FMOD::System* system)
    {
        system->release();
    }

} // namespace System
} // namespace Dynamic_Static
