#pragma once

#include <string>

#include "../app/app_context.hpp"
#include "../store/coord.hpp"

void textElt(
    AppContext& ctx,
    std::string text,
    std::string fontName,
    Coord coord
);
