#ifndef BOX_H
#define BOX_H
#include "Node.h"

namespace UI
{
    class Box : public Node, Style
    {
    public:
        void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) override;
        Box(
            std::optional<uint64_t> _backgroundColor, std::optional<uint64_t> _borderColor, std::optional<uint8_t> _borderThickness);
        void measure(TextManager *textManager, int availableWidth, int availableHeight) override;

        void setPaddingX(int _p) { paddingX = _p; };
    };
}
#endif