#pragma once

#include <sstream>

#include "audio_system.hpp"

void initAudioSystem(AudioSystem& audioSystem);

void cleanUp(AudioSystem& audioSystem);

template <typename T>
inline std::string to_hex(const T& t)
{
    std::stringstream ss;
    ss <<"0x" << std::hex << t;
    return ss.str();
}
