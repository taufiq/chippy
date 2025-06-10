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
}