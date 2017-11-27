
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Time.hpp"

#include "portaudio.h"

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
#include <thread>

struct OggVorbisData final
{
    stb_vorbis* stream { nullptr };
    stb_vorbis_info info { };
    int64_t samples { };
    float duration { };
};

static int oggCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    const PaStreamCallbackFlags statusFlags,
    void* userData
)
{
    auto oggVorbisData = reinterpret_cast<OggVorbisData*>(userData);
    stb_vorbis_get_samples_float_interleaved(
        oggVorbisData->stream,
        oggVorbisData->info.channels,
        reinterpret_cast<float*>(outputBuffer),
        framesPerBuffer * oggVorbisData->info.channels
    );

    auto sample = reinterpret_cast<float*>(outputBuffer);
    for (uint64_t i = 0; i < framesPerBuffer; ++i) {
        *sample++ *= 1;
        *sample++ *= 1;
    }

    oggVorbisData->samples -= framesPerBuffer * oggVorbisData->info.channels;
    return oggVorbisData->samples > 0 ? paContinue : paComplete;
}

int main()
{
    OggVorbisData oggVorbisData;
    std::string filePath = "../../../examples/resources/Track_00.ogg";
    oggVorbisData.stream = stb_vorbis_open_filename(filePath.c_str(), nullptr, nullptr);
    if (!oggVorbisData.stream) {
        std::cerr << "Failed to load ogg @\"" << filePath << "\"" << std::endl;
    }

    oggVorbisData.info = stb_vorbis_get_info(oggVorbisData.stream);
    oggVorbisData.duration = stb_vorbis_stream_length_in_seconds(oggVorbisData.stream);
    oggVorbisData.samples = stb_vorbis_stream_length_in_samples(oggVorbisData.stream) * oggVorbisData.info.channels;
    stb_vorbis_seek_start(oggVorbisData.stream);

    auto error = Pa_Initialize();
    if (error != paNoError) {
        std::cerr << Pa_GetErrorText(error) << std::endl;
    }

    PaStream* audioStream;
    error = Pa_OpenDefaultStream(
        &audioStream,
        0,
        oggVorbisData.info.channels,
        paFloat32,
        oggVorbisData.info.sample_rate,
        oggVorbisData.info.max_frame_size,
        oggCallback,
        &oggVorbisData
    );

    if (error != paNoError) {
        std::cerr << Pa_GetErrorText(error) << std::endl;
    }

    error = Pa_StartStream(audioStream);
    if (error != paNoError) {
        std::cerr << Pa_GetErrorText(error) << std::endl;
    }

    std::this_thread::sleep_for(dst::Second<>(oggVorbisData.duration));

    error = Pa_CloseStream(audioStream);
    if (error != paNoError) {
        std::cerr << Pa_GetErrorText(error) << std::endl;
    }

    error = Pa_Terminate();
    if (error != paNoError) {
        std::cerr << Pa_GetErrorText(error) << std::endl;
    }

    stb_vorbis_close(oggVorbisData.stream);

    return 0;
}
