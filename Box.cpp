#include "Box.h"
#include "SDL.h"
#include "TextManager.h"

namespace UI
{
    Box::Box(std::optional<uint64_t> _backgroundColor,
             std::optional<uint64_t> _borderColor,
             std::optional<uint8_t> _borderThickness)
    {
        if (_backgroundColor)
            backgroundColor = _backgroundColor.value();
        if (_borderColor)
            borderColor = _borderColor.value();
        if (_borderThickness)
            borderThickness = _borderThickness.value();
    };

    void Box::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        SDL_FRect rectangle{
            static_cast<float>(this->getBounds().x),
            static_cast<float>(this->getBounds().y),
            static_cast<float>(this->getBounds().w),
            static_cast<float>(this->getBounds().h)};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rectangle);
        for (auto &child : this->getChildren())
        {
            child->render(renderer, textManager, ctx);
        }
    };

    void Box::measure(TextManager *textManager, int availableWidth, int availableHeight)
    {
        this->bounds.x += this->paddingX;
        this->bounds.y += this->paddingY;
        int x{this->bounds.x}, y{this->bounds.y};
        int rowHeight{0};

        this->bounds.w = availableWidth;

        size_t childrenCount = children.size();
        int originalAvailableWidth{availableWidth};

        for (auto &child : children)
        {
            child->measure(textManager, originalAvailableWidth, availableHeight);
            if (x + this->paddingX + child->getBounds().w > originalAvailableWidth)
            {
                x = this->bounds.x;
                y += rowHeight;
                rowHeight = 0;
            }

            child->setBounds({
                x,
                y,
                child->getBounds().w,
                child->getBounds().h,
            });

            rowHeight = std::max(rowHeight, child->getBounds().h);
            x += child->getBounds().w + this->paddingX;
        }
    }

}
/*
Box -> [Text1, Text2]

I have given W,H.

I have N Texts, each with a variable string length. I have the following constraints.
Do I have a minimumWidth?
I want to avoid this situation.
"
as
d
f
c
a
d
"
If I say I want to fit everything without wrapping, then what happens in the case of a too long text?

Cases:
Width =>
    Original -> if need to wrap, ok! If don't need, ok!
    Modified -> if don't need wrap, render! If need... ?
*/