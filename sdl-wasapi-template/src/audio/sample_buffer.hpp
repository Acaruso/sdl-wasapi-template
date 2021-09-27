#pragma once

struct SampleBuffer
{
    unsigned long* buffer;
    unsigned numSamples;
};

inline SampleBuffer getSampleBuffer(unsigned bufferSizeBytes)
{
    SampleBuffer b = {};
    b.numSamples = bufferSizeBytes / sizeof(unsigned long);
    b.buffer = new unsigned long[b.numSamples];
    return b;
}

inline void zeroSampleBuffer(SampleBuffer sb)
{
    for (unsigned i = 0; i < sb.numSamples; i++) {
        sb.buffer[i] = 0;
    }
}
