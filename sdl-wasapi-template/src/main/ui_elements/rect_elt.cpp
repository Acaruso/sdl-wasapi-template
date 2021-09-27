#include "rect_elt.hpp"

#include "../store/coord.hpp"
#include "../util.hpp"

void rectElt(AppContext& ctx, Rect rect)
{
    ctx.graphicsWrapper.drawRect(rect);
}

void rectEltClickable(
    AppContext& ctx,
    Rect rect,
    std::function<void(AppContext& ctx)> onClick
) {
    bool isInside = isCoordInsideRect(
        ctx.inputSystem.uiState.mousePos,
        rect
    );

    bool isClicked = (
        isInside
        && ctx.inputSystem.uiState.click
        && !ctx.inputSystem.prevUiState.click
    );

    bool isHeld = (
        isInside
        && ctx.inputSystem.uiState.click
    );

    if (isClicked) {
        onClick(ctx);
    }

    if (isHeld) {
        rect.color = Color(255, 0, 0, 255);
    } else {
        rect.color = Color(0, 0, 0, 255);
    }

    ctx.graphicsWrapper.drawRect(rect);
}
