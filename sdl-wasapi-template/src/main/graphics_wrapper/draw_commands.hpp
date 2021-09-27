#pragma once

#include <string>
#include <variant>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/rect.hpp"
#include "font.hpp"
#include "image.hpp"

class DrawRectCommand
{
public:
    Rect rect;
    DrawRectCommand(Rect rect);
    void draw(SDL_Renderer* renderer);
    int getZAxis();
};

class DrawImageCommand
{
public:
    Image image;
    Coord coord;
    DrawImageCommand(Image image, Coord coord);
    void draw(SDL_Renderer* renderer);
    int getZAxis();
};

class DrawTextCommand
{
public:
    std::string text;
    Font font;
    Coord coord;
    DrawTextCommand(std::string text, Font font, Coord coord);
    void draw(SDL_Renderer* renderer);
    int getZAxis();
};

using DrawCommand = std::variant<DrawRectCommand, DrawImageCommand, DrawTextCommand>;
