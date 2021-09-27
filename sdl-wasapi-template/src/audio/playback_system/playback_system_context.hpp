#pragma once

#include "../../lib/readerwriterqueue.h"

struct PlaybackSystemContext
{
    unsigned long sampleCounter;
    double secondsPerSample;
    moodycamel::ReaderWriterQueue<std::string>* queue;
    bool trig{false};

    double getTime()
    {
        return double(sampleCounter) * secondsPerSample;
    }
};
