#pragma once

#include <SDL.h>
#include <SDL_FontCache.h>
#include <SDL_ttf.h>

struct Font
{
    FC_Font* p_font;

    // font height
    int fontSize;
    int fontWidth;
    // height of line -> font + whitespace
    int lineHeight;

    Font() {}

    Font(FC_Font* p_font, int fontSize, int fontWidth, int lineHeight)
        : p_font(p_font), fontSize(fontSize), fontWidth(fontWidth), lineHeight(lineHeight)
    {}
};
