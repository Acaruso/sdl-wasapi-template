#pragma once

#include <functional>

#include "../../lib/readerwriterqueue.h"

#include "../audio_system/audio_system.hpp"
#include "../sample_buffer.hpp"
#include "playback_system_context.hpp"

struct PlaybackSystem
{
    AudioSystem& audioSystem;

    PlaybackSystemContext context;
    SampleBuffer sampleBuffer;
    unsigned bufferSizeBytes;
    unsigned bufferSizeFrames;

    std::function<double(PlaybackSystemContext& context)> callback;

    PlaybackSystem(
        AudioSystem& audioSystem,
        std::function<double(PlaybackSystemContext& context)> callback,
        moodycamel::ReaderWriterQueue<std::string>* queue
    );

    void fillSampleBuffer(size_t numSamplesToWrite);

    void playAudio();
};
