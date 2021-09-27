#pragma once

struct Coord
{
    int x{0};
    int y{0};
    int z{0};

    Coord() {}

    Coord(int x, int y) : x(x), y(y) {}

    Coord(int x, int y, int z) : x(x), y(y), z(z) {}
};
