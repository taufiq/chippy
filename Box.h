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
        void render(SDL_Renderer *renderer, TextManager *textManager, Context ctx) override;
        void measure(TextManager *textManager, float availableWidth, float availableHeight) override;
        void layoutChildrenEvenly(int i, int j, float startingX, float startingY, float availableWidth);
        void setBounds(Bounds _bounds) override;

        void setPaddingX(int _p) { style.paddingX = _p; };
    };
}
#endif