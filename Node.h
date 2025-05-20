#pragma once

#include <vector>
#include <SDL.h>
#include "TextManager.h"

namespace UI
{
    struct Bounds
    {
        int x{}, y{}, w{}, h{};
    };
    struct Context
    {
        UI::Bounds parentBounds{}, additionalBounds{};
    };
    class Node
    {
    protected:
        std::vector<std::unique_ptr<Node>> children;
        struct Bounds bounds{};

    public:
        std::vector<std::unique_ptr<Node>> &getChildren() { return children; };
        virtual void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) = 0;
        void setBounds(Bounds _bounds)
        {
            bounds = _bounds;
        };

        Bounds &getBounds() { return bounds; };
        void addChild(std::unique_ptr<Node> node)
        {
            children.push_back(std::move(node));
        }
        virtual void measure(TextManager *textManager, int availableWidth, int availableHeight) = 0;
        virtual ~Node() = default;
    };

    class Style
    {
    protected:
        uint8_t borderThickness{0};
        uint16_t paddingX{0};
        uint16_t paddingY{0};
        uint64_t backgroundColor{0};
        uint64_t borderColor{0};
        uint64_t textColor{0};
    };
}