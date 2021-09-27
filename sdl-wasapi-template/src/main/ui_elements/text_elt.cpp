#include "text_elt.hpp"

void textElt(
    AppContext& ctx,
    std::string text,
    std::string fontName,
    Coord coord
) {
    ctx.graphicsWrapper.drawText(text, fontName, coord);
}
