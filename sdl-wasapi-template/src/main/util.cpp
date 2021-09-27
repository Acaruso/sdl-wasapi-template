#include "util.hpp"

bool isCoordInsideRect(Coord coord, Rect rect)
{
    return (
        coord.x >= rect.x &&
        coord.y >= rect.y &&
        coord.x <= rect.x + rect.w &&
        coord.y <= rect.y + rect.h
    );
}
