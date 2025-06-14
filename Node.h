#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "TextManager.h"
#include "Vec.h"

/**
 * Okay now only information is being known to the render function of the Node
 * Node has no idea of whether it's being hovered over or not.
 * Right now I have a `scrollForce` that keeps the <(x)offset, (y)scrollForce> in each Node
 * `scrollForce.x` stores the offset relative to the parent, and we propagate the `ctx` down
 * during render.
 *
 * onMouseMove handler is unaware of the offset in render, so it's giving the wrong value
 */
namespace UI
{
    struct Bounds
    {
        float x{}, y{}, w{}, h{};
    };
    struct Context
    {
        Vec2f offset{};
        Vec2f mousePos{};
    };
    enum class Alignment
    {
        LEFT,
        CENTER,
        RIGHT
    };

    class Style
    {
    public:
        uint8_t borderThickness{0};
        uint16_t paddingX{0};
        uint16_t paddingY{0};
        struct Vec4 backgroundColor{0, 0, 0, 255};
        struct Vec4 borderColor{0, 0, 0, 255};
        struct Vec4 textColor{255, 255, 255, 255};
        Alignment alignment{Alignment::CENTER};
        int flex{1};
    };
    class Node
    {
    protected:
        std::vector<std::unique_ptr<Node>> children;

        struct Bounds bounds{};

    public:
        std::vector<std::unique_ptr<Node>> &getChildren() { return children; };
        bool isMouseOver{false};
        Node *parent{nullptr};
        Vec2f scrollForce{}; // Storing as <offset, yForce>
        bool scrollable{false};
        Style style{};
        virtual void handleScroll(SDL_MouseWheelEvent event);
        virtual void onMouseMove(float x, float y);
        virtual void render(SDL_Renderer *renderer, TextManager *textManager, Context ctx) = 0;
        virtual void setBounds(Bounds _bounds)
        {
            bounds = _bounds;
        };

        void setBoundsRecursive(Bounds _bounds)
        {
            float dX{_bounds.x - bounds.x}, dY{_bounds.y - bounds.y};
            for (auto &child : children)
            {
                // We recursively offset child elements with the new position shift
                Bounds childBounds{child->getBounds()};
                child->setBoundsRecursive({childBounds.x + dX,
                                           childBounds.y + dY,
                                           childBounds.w,
                                           childBounds.h});
            }
            Node::setBounds(_bounds);
        }
        Bounds &getBounds() { return bounds; };
        void addChild(std::unique_ptr<Node> node)
        {
            node->parent = this;
            children.push_back(std::move(node));
        }
        virtual void measure(TextManager *textManager, float availableWidth, float availableHeight) = 0;
        virtual ~Node() = default;
    };
}