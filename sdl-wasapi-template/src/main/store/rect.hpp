#pragma once

#include "color.hpp"

struct Rect
{
    int x{0};
    int y{0};
    int z{0};
    int w{0};
    int h{0};
    Color color;

    Rect() {}

    Rect(int x, int y, int w, int h, Color color)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
    }

    Rect(int x, int y, int z, int w, int h, Color color)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->h = h;
        this->color = color;
    }
};
