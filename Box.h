#ifndef BOX_H
#define BOX_H
#include "Node.h"

namespace UI
{
    class Box : public Node
    {
    public:
        void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) override;
        void measure(TextManager *textManager, int availableWidth, int availableHeight) override;

        void setPaddingX(int _p) { style.paddingX = _p; };
    };
}
#endif