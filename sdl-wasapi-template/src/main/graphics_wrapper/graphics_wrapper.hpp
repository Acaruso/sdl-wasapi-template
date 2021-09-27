#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_FontCache.h>
#include <SDL_ttf.h>

#include "../store/coord.hpp"
#include "../store/rect.hpp"
#include "draw_system.hpp"
#include "font.hpp"
#include "image.hpp"

class GraphicsWrapper
{
public:
    std::string windowTitle;

    int screenWidth;
    int screenHeight;

    SDL_Window* window;
    SDL_Surface* windowSurface;
    SDL_Renderer* windowRenderer;

    std::unordered_map<std::string, Image> images;
    std::unordered_map<std::string, Font> fonts;

    DrawSystem drawSystem;

    GraphicsWrapper() {}

    void init();
    void clearWindow();

    void drawRect(Rect rect);
    void drawImage(std::string name, Coord coord);
    void drawText(std::string text, std::string fontName, Coord coord);

    void loadImage(std::string name, std::string path);

    void loadFont(
        std::string name,
        std::string path,
        int fontSize,
        int fontWidth,
        int lineHeight
    );

    void render();
    void destroyWindow();
    void quit();
};
