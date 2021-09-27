#pragma once

#include "../lib/readerwriterqueue.h"

int audioEntrypoint(moodycamel::ReaderWriterQueue<std::string>* queue);
