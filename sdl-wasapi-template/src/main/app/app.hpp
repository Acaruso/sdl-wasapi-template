#pragma once

#include <functional>

#include "app_context.hpp"

struct App
{
    AppContext context;

    std::function<void(AppContext& context)> setup;
    std::function<void(AppContext& context)> callback;

    App(
        std::function<void(AppContext& context)> setup,
        std::function<void(AppContext& context)> callback
    );

    void run();
};
