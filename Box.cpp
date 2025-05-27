#include "Box.h"
#include <SDL3/SDL.h>
#include "TextManager.h"
#include <utility>

namespace UI
{
    void Box::setBounds(Bounds _bounds)
    {
        float dX{_bounds.x - bounds.x}, dY{_bounds.y - bounds.y};
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
            getBounds().x,
            getBounds().y,
            getBounds().w,
            getBounds().h};
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

    void Box::layoutChildrenEvenly(int i, int j, float startingX, float startingY, float availableWidth)
    {
        size_t rowChildrenCount = j - i;
        float widthPerChildren = availableWidth / rowChildrenCount;
        for (int k{i}; k < j; k++)
        {
            auto &rowChild = children.at(k);
            // We re-set the x coordinate, and width
            // whilst keeping the y coordinate, and height the same
            rowChild->setBounds({startingX + widthPerChildren * (k - i),
                                 startingY,
                                 widthPerChildren,
                                 rowChild->getBounds().h});
        }
    }

    void Box::measure(TextManager *textManager, float availableWidth, float availableHeight)
    {
        float startingX{bounds.x + style.paddingX}, startingY{bounds.y + style.paddingY};
        availableWidth -= style.paddingX * 2;
        float x{startingX}, y{startingY};
        float rowHeight{0}, totalHeight{0};

        int begin{0};

        setBounds({x, y, availableWidth, getBounds().h});
        for (size_t i{0}; i < children.size(); i++)
        {
            auto &child = children.at(i);
            child->measure(textManager, availableWidth, availableHeight);
            if (x + child->getBounds().w > availableWidth)
            {
                Box::layoutChildrenEvenly(begin, i, startingX, y, availableWidth);
                x = startingX;
                y += rowHeight;
                totalHeight += rowHeight;
                rowHeight = 0;
                begin = i;
            }
            rowHeight = std::max(rowHeight, child->getBounds().h);
            child->setBounds({x,
                              y,
                              child->getBounds().w,
                              child->getBounds().h});
            x += child->getBounds().w;
        }
        Box::layoutChildrenEvenly(begin, children.size(), startingX, y, availableWidth);
        totalHeight += rowHeight;
        setBounds({
            getBounds().x,
            getBounds().y,
            getBounds().w,
            totalHeight,
        });
    }
}