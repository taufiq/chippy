#include "Node.h"

namespace UI
{
    void Node::onMouseMove(float x, float y)
    {
        // scroll offset
        y -= scrollForce.x;

        if (x >= bounds.x &&
            x <= bounds.x + bounds.w &&
            y >= bounds.y &&
            y <= bounds.y + bounds.h)
        {
            isMouseOver = true;
        }
        else
        {
            isMouseOver = false;
        }

        // relative positioning
        y -= bounds.y;
        x -= bounds.x;
        for (auto &child : children)
        {
            child->onMouseMove(x, y);
        }
    }
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