#pragma once

#include <variant>
#include <vector>

#include "../store/rect.hpp"
#include "draw_commands.hpp"

class DrawSystem
{
private:
    std::vector<DrawCommand> drawQueue;

public:
    void push(DrawCommand command);
    void draw(SDL_Renderer* windowRenderer);
};
