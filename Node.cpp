#include "Node.h"

namespace UI
{
    void Node::onMouseMove(float x, float y)
    {
        for (auto &child : children)
        {
            if (x >= static_cast<float>(child->bounds.x) &&
                x <= static_cast<float>(child->bounds.x + child->bounds.w) &&
                y >= static_cast<float>(child->bounds.y) &&
                y <= static_cast<float>(child->bounds.y + child->bounds.h))
            {
                child->isMouseOver = true;
            }
            else
            {
                child->isMouseOver = false;
            }
            child->onMouseMove(x, y);
        }
    }
    // Try to propagate scroll Event down
    void Node::handleScroll(SDL_MouseWheelEvent event)
    {
        float x{event.mouse_x}, y{event.mouse_y};
        if (scrollable)
        {
            scrollForce.y = event.y;
            return;
        }
        for (auto &child : children)
        {
            if (x >= child->bounds.x &&
                x <= child->bounds.x + child->bounds.w &&
                y >= child->bounds.y &&
                y <= child->bounds.y + child->bounds.h)
            {
                child->handleScroll(event);
            }
        }
    }
}