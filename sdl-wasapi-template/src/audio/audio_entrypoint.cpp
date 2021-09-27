#include "audio_entrypoint.hpp"

#include <comdef.h>
#include <iostream>
#include <string>

#include "audio_system/audio_system.hpp"
#include "audio_system/init.hpp"
#include "callback/audio_callback.hpp"
#include "playback_system/playback_system.hpp"

int audioEntrypoint(moodycamel::ReaderWriterQueue<std::string>* queue)
{
    // initialize COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    AudioSystem audioSystem = {};

    try {
        initAudioSystem(audioSystem);

        PlaybackSystem playbackSystem(audioSystem, audioCallback, queue);

        // begin main loop
        playbackSystem.playAudio();
    }
    catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    cleanUp(audioSystem);
    return 0;
}
