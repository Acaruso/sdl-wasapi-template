#pragma once

#include <SDL.h>

struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color() {}

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};
