#include "Box.h"
#include <SDL3/SDL.h>
#include "TextManager.h"
#include <utility>

namespace UI
{
    void Box::setBounds(Bounds _bounds)
    {
        int dX{_bounds.x - bounds.x}, dY{_bounds.y - bounds.y};
        for (auto &child : children)
        {
            // We recursively offset child elements with the new position shift
            Bounds childBounds{child->getBounds()};
            child->setBounds({childBounds.x + dX,
                              childBounds.y + dY,
                              childBounds.w,
                              childBounds.h});
        }
        Node::setBounds(_bounds);
    }
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
        int startingX{bounds.x}, startingY{bounds.y};
        int x{startingX}, y{startingY};
        int rowHeight{0}, totalHeight{0};

        setBounds({x, y, availableWidth, getBounds().h});
        for (size_t i{0}; i < children.size(); i++)
        {
            auto &child = children.at(i);
            child->measure(textManager, availableWidth, availableHeight);
            if (x + child->getBounds().w > availableWidth)
            {
                x = startingX;
                y += rowHeight;
                totalHeight += rowHeight;
                rowHeight = 0;
            }
            rowHeight = std::max(rowHeight, child->getBounds().h);
            child->setBounds({x,
                              y,
                              child->getBounds().w,
                              child->getBounds().h});
            x += child->getBounds().w;
        }
        totalHeight += rowHeight;
        setBounds({
            getBounds().x,
            getBounds().y,
            getBounds().w,
            totalHeight,
        });
    }
}
// }
/**
 * Box -> Measure its children
 * Children returns height
 * Box child
 * -> Text -> Text::measure()
 * -> Box -> Box::measure()
 *
 */