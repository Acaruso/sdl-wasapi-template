#include "app.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "../../lib/readerwriterqueue.h"

#include "../../audio/audio_entrypoint.hpp"
#include "../ui_elements/rect_elt.hpp"

App::App(
    std::function<void(AppContext& context)> setup,
    std::function<void(AppContext& context)> callback
)
    : setup(setup), callback(callback)
{
    this->context.graphicsWrapper.init();
}

void App::run()
{
    std::thread th(&audioEntrypoint, &(this->context.queue));

    // call setup ///////////////////
    this->setup(this->context);

    while (!this->context.inputSystem.uiState.quit) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        this->context.graphicsWrapper.clearWindow();
        this->context.inputSystem.run();

        // call callback ///////////////////
        this->callback(this->context);

        this->context.graphicsWrapper.render();
        this->context.inputSystem.nextState();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        Uint32 dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        Uint32 time_to_delay = dur > 10 ? 0 : 10 - dur;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_delay));
    }

    std::cout << "quitting" << std::endl;

    this->context.queue.enqueue("quit");
    th.join();

    this->context.graphicsWrapper.destroyWindow();
    this->context.graphicsWrapper.quit();
}
