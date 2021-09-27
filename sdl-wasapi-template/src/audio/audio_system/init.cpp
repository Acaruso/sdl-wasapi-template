#include "init.hpp"

#include <Avrt.h>
#include <string>

REFERENCE_TIME REFTIMES_PER_SEC = 10000000;

void getEnumerator(AudioSystem& audioSystem)
{
    CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
    IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

    IMMDeviceEnumerator* enumerator = NULL;

    HRESULT hr = CoCreateInstance(
        CLSID_MMDeviceEnumerator,
        NULL,
        CLSCTX_ALL,
        IID_IMMDeviceEnumerator,
        (void**)&enumerator
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": getEnumerator");
    } else {
        std::cout << "SUCCESS: getEnumerator" << std::endl;
    }

    audioSystem.enumerator = enumerator;
}

void getDevice(AudioSystem& audioSystem)
{
    IMMDevice* device = NULL;

    HRESULT hr = audioSystem.enumerator->GetDefaultAudioEndpoint(
        eRender,
        eConsole,
        &device
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": getDevice");
    } else {
        std::cout << "SUCCESS: getDevice" << std::endl;
    }

    audioSystem.device = device;
}

void getAudioClient(AudioSystem& audioSystem)
{
    IAudioClient* client = NULL;
    IID IID_IAudioClient = __uuidof(IAudioClient);

    HRESULT hr = audioSystem.device->Activate(
        IID_IAudioClient,
        CLSCTX_ALL,
        NULL,
        (void**)&client
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": getAudioClient");
    } else {
        std::cout << "SUCCESS: getAudioClient" << std::endl;
    }

    audioSystem.audioClient = client;
}

void getDevicePeriod(AudioSystem& audioSystem, REFERENCE_TIME& devicePeriod)
{
    REFERENCE_TIME defaultDevicePeriod = 0;
    REFERENCE_TIME minimumDevicePeriod = 0;

    HRESULT hr = audioSystem.audioClient->GetDevicePeriod(&defaultDevicePeriod, &minimumDevicePeriod);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": getDevicePeriod");
    } else {
        std::cout << "SUCCESS: getDevicePeriod" << std::endl;
    }

    devicePeriod = minimumDevicePeriod;
}

WAVEFORMATEXTENSIBLE getWaveFormat()
{
    WAVEFORMATEXTENSIBLE w = {};

    w.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    w.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
    w.Format.cbSize = 22;
    w.Format.nChannels = 2;
    w.Format.nSamplesPerSec = 44100;
    w.Format.wBitsPerSample = 32;
    w.Samples.wValidBitsPerSample = 24;
    w.Format.nBlockAlign = (w.Format.nChannels * w.Format.wBitsPerSample) / 8;
    w.Format.nAvgBytesPerSec = w.Format.nSamplesPerSec * w.Format.nBlockAlign;

    return w;
}

void checkFormatSupport(AudioSystem& audioSystem)
{
    WAVEFORMATEX match = {0};
    WAVEFORMATEX* p_match = &match;
    
    HRESULT hr = audioSystem.audioClient->IsFormatSupported(
        AUDCLNT_SHAREMODE_SHARED,
        &audioSystem.waveFormat.Format,
        &p_match
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": checkFormatSupport");
    } else {
        std::cout << "SUCCESS: checkFormatSupport" << std::endl;
    }
}

void initAudioClient(AudioSystem& audioSystem, REFERENCE_TIME minimumDevicePeriod)
{
    std::cout << "minimumDevicePeriod: " << minimumDevicePeriod << std::endl;

    HRESULT hr = audioSystem.audioClient->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
        minimumDevicePeriod,
        0,
        &audioSystem.waveFormat.Format,
        NULL
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": initAudioClient");
    } else {
        std::cout << "SUCCESS: initAudioClient" << std::endl;
    }
}

void getRenderClient(AudioSystem& audioSystem)
{
    IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);
    IAudioRenderClient *renderClient = NULL;

    HRESULT hr = audioSystem.audioClient->GetService(
        IID_IAudioRenderClient,
        (void**)&renderClient
    );

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": getRenderClient");
    } else {
        std::cout << "SUCCESS: getRenderClient" << std::endl;
    }

    audioSystem.renderClient = renderClient;
}

void initEvent(AudioSystem& audioSystem)
{
    HANDLE hEvent = CreateEvent(nullptr, false, false, nullptr);

    if (hEvent == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("ERROR: CreateEvent");
    }

    HRESULT hr = audioSystem.audioClient->SetEventHandle(hEvent);

    if (FAILED(hr)) {
        throw std::runtime_error("ERROR " + to_hex(hr) + ": initEvent");
    } else {
        std::cout << "SUCCESS: initEvent" << std::endl;
    }

    audioSystem.hEvent = hEvent;
}

void initTask(AudioSystem& audioSystem)
{
    // increase thread priority
    unsigned long taskIndex = 0;
    audioSystem.hTask = AvSetMmThreadCharacteristics(TEXT("Pro Audio"), &taskIndex);

    if (audioSystem.hTask == NULL) {
        throw std::runtime_error("ERROR: initTask");
    } else {
        std::cout << "SUCCESS: initTask" << std::endl;
    }
}

void initAudioSystem(AudioSystem& audioSystem)
{
    getEnumerator(audioSystem);

    getDevice(audioSystem);

    getAudioClient(audioSystem);

    audioSystem.waveFormat = getWaveFormat();

    checkFormatSupport(audioSystem);

    REFERENCE_TIME minimumDevicePeriod = 0;

    getDevicePeriod(audioSystem, minimumDevicePeriod);

    initAudioClient(audioSystem, minimumDevicePeriod);

    getRenderClient(audioSystem);

    initEvent(audioSystem);

    initTask(audioSystem);
}

void cleanUp(AudioSystem& audioSystem)
{
    if (audioSystem.enumerator != NULL) {
        audioSystem.enumerator->Release();
    }

    if (audioSystem.device != NULL) {
        audioSystem.device->Release();
    }

    if (audioSystem.audioClient != NULL) {
        audioSystem.audioClient->Release();
    }

    if (audioSystem.renderClient != NULL) {
        audioSystem.renderClient->Release();
    }

    if (audioSystem.hEvent != NULL) {
        CloseHandle(audioSystem.hEvent);
    }

    if (audioSystem.hTask != NULL) {
        AvRevertMmThreadCharacteristics(audioSystem.hTask);
    }
}
