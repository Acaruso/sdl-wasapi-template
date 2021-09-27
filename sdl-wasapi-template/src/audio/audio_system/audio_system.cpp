#include "audio_system.hpp"

#include "init.hpp"

#include <string>

unsigned AudioSystem::getBufferSizeFrames()
{
    unsigned bufferSize;
    HRESULT hr = this->audioClient->GetBufferSize(&bufferSize);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + std::to_string(hr) + ": GetBufferSize");
    }

    return bufferSize;
}

unsigned AudioSystem::getBufferSizeBytes()
{
    unsigned bufferSizeFrames = this->getBufferSizeFrames();

    unsigned bufferSizeBytes = (
        (
            bufferSizeFrames
            * this->waveFormat.Format.nChannels
            * this->waveFormat.Format.wBitsPerSample
        ) / 8
    );

    return bufferSizeBytes;
}

void AudioSystem::writeBuffer(unsigned long* source, unsigned numFramesToWrite)
{
    HRESULT hr;
    BYTE *dest = NULL;

    unsigned bufferSizeFrames = this->getBufferSizeFrames();

    unsigned bufferSizeBytes = this->getBufferSizeBytes();

    // after this call, dest will point to location in buffer to write to
    hr = this->renderClient->GetBuffer(numFramesToWrite, &dest);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + std::to_string(hr) + ": GetBuffer");
    }

    memcpy(
        dest,
        source,
        sizeof(unsigned long) * 2 * numFramesToWrite
    );

    hr = this->renderClient->ReleaseBuffer(numFramesToWrite, 0);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + std::to_string(hr) + ": ReleaseBuffer");
    }
}

unsigned AudioSystem::getCurrentPadding()
{
    unsigned numPaddingFrames = 0;
    HRESULT hr = this->audioClient->GetCurrentPadding(&numPaddingFrames);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + std::to_string(hr) + ": GetCurrentPadding");
    }

    return numPaddingFrames;
}

void AudioSystem::startPlaying()
{
    HRESULT hr = this->audioClient->Start();

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + std::to_string(hr) + ": Start");
    }
}

void AudioSystem::stopPlaying()
{
    HRESULT hr = this->audioClient->Stop();

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + std::to_string(hr) + ": Stop");
    }
}
