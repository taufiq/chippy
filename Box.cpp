#include "Box.h"
#include "SDL.h"
#include "TextManager.h"

namespace UI
{
    void Box::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        SDL_FRect rectangle{
            static_cast<float>(this->getBounds().x),
            static_cast<float>(this->getBounds().y),
            static_cast<float>(this->getBounds().w),
            static_cast<float>(this->getBounds().h)};
        SDL_SetRenderDrawColor(
            renderer,
            this->style.backgroundColor.x,
            this->style.backgroundColor.y,
            this->style.backgroundColor.z,
            this->style.backgroundColor.w);
        SDL_RenderFillRect(renderer, &rectangle);
        for (auto &child : this->getChildren())
        {
            child->render(renderer, textManager, ctx);
        }
    };

    void Box::measure(TextManager *textManager, int availableWidth, int availableHeight)
    {
        int x{this->bounds.x}, y{this->bounds.y};
        int rowHeight{0};

        this->bounds.w = availableWidth;

        size_t childrenCount = children.size();

        for (auto &child : children)
        {
            child->measure(textManager, availableWidth, availableHeight);
            if (x + this->style.paddingX + child->getBounds().w > availableWidth)
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
            x += child->getBounds().w + this->style.paddingX;
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