
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_FMOD_ENABLED

#include "fmod.hpp"

namespace dst {
namespace sys {

    inline FMOD::System* fmod_init()
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

    inline void fmod_update(FMOD::System* system)
    {
        system->update();
    }

    inline void fmod_shutdown(FMOD::System* system)
    {
        system->release();
    }

} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_FMOD_ENABLED
