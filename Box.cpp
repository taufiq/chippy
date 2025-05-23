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
        if (layoutMode == LayoutMode::HORIZONTAL)
        {
            int rowHeight{0};
            this->bounds.w = availableWidth;

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
        else
        {
            int rowHeight{0};
            this->bounds.h = availableHeight;

            for (auto &child : children)
            {
                child->measure(textManager, availableWidth, availableHeight);
                if (y + this->style.paddingY + child->getBounds().h > availableHeight)
                {
                    y = this->bounds.y;
                    x += rowHeight;
                    rowHeight = 0;
                }

                child->setBounds({
                    x,
                    y,
                    child->getBounds().w,
                    child->getBounds().h,
                });

                rowHeight = std::max(rowHeight, child->getBounds().h);
                y += child->getBounds().h + this->style.paddingY;
            }
        }
    }

}