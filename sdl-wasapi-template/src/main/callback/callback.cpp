#include "callback.hpp"

#include <iostream>

#include "../ui_elements/image_elt.hpp"
#include "../ui_elements/rect_elt.hpp"
#include "../ui_elements/text_elt.hpp"

void setup(AppContext& context)
{
    context.graphicsWrapper.loadImage("smiley", "src/images/smiley.png");

    context.graphicsWrapper.loadFont(
        "dos",
        "src/images/Perfect-DOS-VGA-437.ttf",
        16,
        9,
        20
    );
}

void callback(AppContext& context)
{
    auto onClick = [](AppContext &ctx){
        std::cout << "clicked" << std::endl;
        ctx.queue.enqueue("trig");
    };

    rectEltClickable(
        context,
        Rect(50, 50, 50, 50, Color(0x00, 0xFF, 0x00, 0xFF)),
        onClick
    );

    rectElt(
        context,
        Rect(55, 55, 2, 50, 50, Color(0xFF, 0xFF, 0x00, 0xFF))
    );

    imageElt(context, "smiley", Coord(0, 0, 0));

    textElt(context, "test text", "dos", Coord(0, 0, 2));
}
