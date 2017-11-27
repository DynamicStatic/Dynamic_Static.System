
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Audio/AudioTest.hpp"

#ifdef DYNAMIC_STATIC_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4996)
#endif

#include <string>
#include "stb_vorbis.c"

#ifdef DYNAMIC_STATIC_MSVC
    #pragma warning(pop)
#endif

#include <iostream>
#include <string>

namespace Dynamic_Static {
namespace System {

    void AudioTest::play()
    {
        std::string filePath = "D:/Dynamic_Static/Dynamic_Static.System/examples/resources/PegboardNerds_x_MisterWives-Coffins-FreeRelease.ogg";

        int channels;
        int sampleRate;
        short* output;
        int rc = stb_vorbis_decode_filename(filePath.c_str(), &channels, &sampleRate, &output);
        if (rc == -1) {
            std::cerr << "No good" << std::endl;
        }
    }

} // namespace System
} // namespace Dynamic_Static
