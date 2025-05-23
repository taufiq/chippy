#include "Node.h"

namespace UI
{
    class Canvas : public Node
    {
    public:
        std::unique_ptr<Vec4[]> pixels{nullptr};

        Canvas(int w, int h)
        {
            Canvas::setBounds({
                .w = w,
                .h = h,
            });
        }

        void setBounds(Bounds _bounds) override;
        void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) override;
        void measure(TextManager *textManager, int availableWidth, int availableHeight) override;
    };
}