#include "Box.h"
#include "SDL.h"
#include "TextManager.h"

namespace UI
{
    void Box::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        SDL_FRect rectangle{
            static_cast<float>(getBounds().x),
            static_cast<float>(getBounds().y),
            static_cast<float>(getBounds().w),
            static_cast<float>(getBounds().h)};
        SDL_SetRenderDrawColor(
            renderer,
            style.backgroundColor.x,
            style.backgroundColor.y,
            style.backgroundColor.z,
            style.backgroundColor.w);
        SDL_RenderFillRect(renderer, &rectangle);
        for (auto &child : getChildren())
        {
            child->render(renderer, textManager, ctx);
        }
    };

    void Box::layoutChildrenEvenly(int i, int j, int startingX, int startingY, int availableWidth)
    {
        size_t rowChildrenCount = j - i;
        int widthPerChildren = availableWidth / rowChildrenCount;
        for (int k{i}; k < j; k++)
        {
            auto &rowChild = children.at(k);
            // We re-set the x coordinate, and width
            // whilst keeping the y coordinate, and height the same
            rowChild->setBounds({static_cast<int>(startingX + widthPerChildren * (k - i)),
                                 startingY,
                                 widthPerChildren,
                                 rowChild->getBounds().h});
        }
    }

    void Box::measure(TextManager *textManager, int availableWidth, int availableHeight)
    {
        int startingX{bounds.x + style.paddingX}, startingY{bounds.y + style.paddingY};
        int x{bounds.x + style.paddingX}, y{bounds.y + style.paddingY};
        if (layoutMode == LayoutMode::HORIZONTAL)
        {
            int rowHeight{0};
            bounds.w = availableWidth;

            int availableWidthForChildren = availableWidth - style.paddingX * 2;

            // Range to keep track of children row count
            // used for doing a second pass to distribute children evenly
            // [begin, i)
            size_t begin{0};
            for (size_t i{0}; i < children.size(); i++)
            {
                auto &child = children.at(i);
                child->measure(textManager, availableWidthForChildren, availableHeight);

                if (x + child->getBounds().w > availableWidthForChildren)
                {
                    Box::layoutChildrenEvenly(begin, i, startingX, y, availableWidthForChildren);
                    begin = i;
                    x = startingX;
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
                x += child->getBounds().w;
            }
            Box::layoutChildrenEvenly(begin, children.size(), startingX, y, availableWidthForChildren);
        }
    }

}