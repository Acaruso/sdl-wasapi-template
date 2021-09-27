#pragma once

#include <functional>

#include "../app/app_context.hpp"
#include "../store/rect.hpp"

void rectElt(AppContext& ctx, Rect rect);

void rectEltClickable(
    AppContext& ctx,
    Rect rect,
    std::function<void(AppContext& ctx)> onClick
);
