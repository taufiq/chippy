#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "TextManager.h"
#include "Vec.h"

namespace UI
{
    struct Bounds
    {
        int x{}, y{}, w{}, h{};
    };
    struct Context
    {
        [[maybe_unused]] UI::Bounds parentBounds{}, additionalBounds{};
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
        Node *parent{nullptr};
        Style style{};
        virtual void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) = 0;
        virtual void setBounds(Bounds _bounds)
        {
            bounds = _bounds;
        };

        Bounds &getBounds() { return bounds; };
        void addChild(std::unique_ptr<Node> node)
        {
            node->parent = this;
            children.push_back(std::move(node));
        }
        virtual void measure(TextManager *textManager, int availableWidth, int availableHeight) = 0;
        virtual ~Node() = default;
    };
}