#include "image_elt.hpp"

void imageElt(
    AppContext& ctx,
    std::string name,
    Coord coord
) {
    ctx.graphicsWrapper.drawImage(name, coord);
}
