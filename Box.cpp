#include "Box.h"
#include <SDL3/SDL.h>
#include "TextManager.h"
#include <utility>

namespace UI
{
    // Recursively set relPos
    void Box::setBounds(Bounds _bounds)
    {
        // I don't have to override and recursively set
        // Cause now I'm calling measure every loop
        // So it takes n iterations to do this recursive process automatically

        // float dX{_bounds.x - bounds.x}, dY{_bounds.y - bounds.y};
        // for (auto &child : children)
        // {
        //     // We recursively offset child elements with the new position shift
        //     Bounds childBounds{child->getBounds()};
        //     child->setBounds({childBounds.x + dX,
        //                       childBounds.y + dY,
        //                       childBounds.w,
        //                       childBounds.h});
        // }
        Node::setBounds(_bounds);
    }
    void Box::render(SDL_Renderer *renderer, TextManager *textManager, Context ctx)
    {
        auto roundingFunction = scrollForce.y >= 0 ? std::floorf : std::ceilf;
        scrollForce.y = roundingFunction(scrollForce.y * 10) / 11.4f;
        scrollForce.x += scrollForce.y;
        SDL_FRect rectangle{
            getBounds().x,
            getBounds().y + ctx.offset.y + scrollForce.x,
            getBounds().w,
            getBounds().h};
        SDL_SetRenderDrawColor(
            renderer,
            style.backgroundColor.x,
            style.backgroundColor.y,
            style.backgroundColor.z,
            style.backgroundColor.w);
        SDL_RenderFillRect(renderer, &rectangle);

        ctx.offset.y += scrollForce.x;
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
        float startingX{bounds.x}, startingY{bounds.y};
        availableWidth -= style.paddingX * 2;
        float x{startingX + style.paddingX}, y{startingY + style.paddingX};
        float rowHeight{0}, totalHeight{0};

        int begin{0};

        setBounds({startingX, startingY, availableWidth, getBounds().h});
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
            startingX,
            startingY,
            getBounds().w,
            totalHeight,
        });
    }
}