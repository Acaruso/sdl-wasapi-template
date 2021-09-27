#include "playback_system.hpp"

#include "../audio_util.hpp"

PlaybackSystem::PlaybackSystem(
    AudioSystem& audioSystem,
    std::function<double(PlaybackSystemContext& context)> callback,
    moodycamel::ReaderWriterQueue<std::string>* queue
)
    : audioSystem(audioSystem), callback(callback)
{
    this->context.sampleCounter = 0;

    unsigned long samplesPerSecond = this->audioSystem.waveFormat.Format.nSamplesPerSec;
    this->context.secondsPerSample = 1.0 / (double)samplesPerSecond;

    this->context.queue = queue;

    this->bufferSizeBytes = this->audioSystem.getBufferSizeBytes();
    this->sampleBuffer = getSampleBuffer(this->bufferSizeBytes);

    this->bufferSizeFrames = audioSystem.getBufferSizeFrames();
}

void PlaybackSystem::playAudio()
{
    zeroSampleBuffer(this->sampleBuffer);

    audioSystem.writeBuffer(this->sampleBuffer.buffer, this->bufferSizeFrames);

    audioSystem.startPlaying();

    std::string s;

    // main loop:
    while (true) {
        WaitForSingleObject(audioSystem.hEvent, INFINITE);

        // handle events from main thread
        if (this->context.queue->try_dequeue(s)) {
            if (s == "quit") {
                std::cout << "thread: " << s << std::endl;
                break;
            }
            
            if (s == "trig") {
                this->context.trig = true;
            }
        } else {
            this->context.trig = false;
        }

        unsigned numPaddingFrames = audioSystem.getCurrentPadding();

        // recall that each elt of buffer stores 1 sample
        // frame is 2 samples -> 1 for each channel
        // so numSamplesToWrite is 2x numFramesToWrite

        unsigned numFramesToWrite = this->bufferSizeFrames - numPaddingFrames;

        unsigned numSamplesToWrite = numFramesToWrite * 2;

        this->fillSampleBuffer(numSamplesToWrite);

        audioSystem.writeBuffer(this->sampleBuffer.buffer, numFramesToWrite);
    }

    audioSystem.stopPlaying();
}

void PlaybackSystem::fillSampleBuffer(size_t numSamplesToWrite)
{
    unsigned numChannels = 2;

    for (int i = 0; i < numSamplesToWrite; i += numChannels) {
        
        // call callback //////////////////////
        double sig = this->callback(this->context);

        unsigned samp = scaleSignal(sig);

        this->sampleBuffer.buffer[i] = samp;       // L
        this->sampleBuffer.buffer[i + 1] = samp;   // R

        this->context.sampleCounter++;
    }
}
