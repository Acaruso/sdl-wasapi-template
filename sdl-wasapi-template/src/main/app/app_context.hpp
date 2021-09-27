#pragma once

#include "../../lib/readerwriterqueue.h"

#include "../graphics_wrapper/graphics_wrapper.hpp"
#include "../store/store.hpp"
#include "../systems/input_system/input_system.hpp"

struct AppContext
{
    GraphicsWrapper graphicsWrapper;
    InputSystem inputSystem;
    Store store;
    moodycamel::ReaderWriterQueue<std::string> queue;

    AppContext() 
    {
        queue = moodycamel::ReaderWriterQueue<std::string>(100);
    }
};
