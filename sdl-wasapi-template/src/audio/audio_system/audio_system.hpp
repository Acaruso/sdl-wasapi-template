#pragma once

#include <Audioclient.h>
#include <iostream>
#include <mmdeviceapi.h>

struct AudioSystem
{
    IMMDeviceEnumerator* enumerator;
    IMMDevice* device;
    IAudioClient* audioClient;
    IAudioRenderClient* renderClient;
    WAVEFORMATEXTENSIBLE waveFormat;
    HANDLE hEvent;
    HANDLE hTask;

    unsigned getBufferSizeFrames();
    unsigned getBufferSizeBytes();
    unsigned getCurrentPadding();
    void writeBuffer(unsigned long* source, unsigned numFramesToWrite);
    void startPlaying();
    void stopPlaying();
};
