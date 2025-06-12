#include "Node.h"

namespace UI
{
    void Node::onMouseMove(float x, float y)
    {
        // yOffset is relative to the parent
        // mousePos starts absolute
        // so everytime I enter an element, I check if currentPos is within defined bounds + bounds offset
        // Then I minus the cursor position when I enter its child
        if (x >= bounds.x &&
            x <= bounds.x + bounds.w &&
            y >= bounds.y + scrollForce.x &&
            y <= bounds.y + bounds.h + scrollForce.y)
        {
            isMouseOver = true;
        }
        else
        {
            isMouseOver = false;
        }
        for (auto &child : children)
        {
            child->onMouseMove(x, y - scrollForce.x);
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