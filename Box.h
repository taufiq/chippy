#ifndef BOX_H
#define BOX_H
#include "Node.h"

namespace UI
{

    enum class LayoutMode
    {
        HORIZONTAL,
        VERTICAL,
    };

    class Box : public Node
    {
    private:
        LayoutMode layoutMode{LayoutMode::HORIZONTAL};

    public:
        void setLayoutMode(LayoutMode _layoutMode) { layoutMode = _layoutMode; };
        void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) override;
        void measure(TextManager *textManager, int availableWidth, int availableHeight) override;
        void layoutChildrenEvenly(int i, int j, int startingX, int startingY, int availableWidth);

        void setPaddingX(int _p) { style.paddingX = _p; };
    };
}
#endif