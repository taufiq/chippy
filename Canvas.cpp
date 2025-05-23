#include "Canvas.h"
#include <SDL.h>
#include "Vec.h"

namespace UI
{
    // TODO: The way `setBounds` is currently set up is that it loses data when resizing the canvas.
    // Figure a way out to preserve it.
    void Canvas::setBounds(Bounds _bounds)
    {
        int oldSize{bounds.w * bounds.h};
        int newSize{_bounds.w * _bounds.h};

        std::unique_ptr<Vec4[]> newPixels = std::make_unique<Vec4[]>(newSize);

        // Transfer pixel data when resizing
        if (pixels)
        {
            for (int i{0}; i < std::min(oldSize, newSize); i++)
            {
                newPixels[i] = pixels[i];
            }
        }
        pixels = std::move(newPixels);

        Node::setBounds(_bounds);
    }

    void Canvas::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        for (int i{0}; i < bounds.w * bounds.h; i++)
        {
            SDL_SetRenderDrawColor(renderer,
                                   this->pixels[i].x,
                                   this->pixels[i].y,
                                   this->pixels[i].z,
                                   this->pixels[i].w);
            float x{static_cast<float>(i % bounds.w)},
                y{static_cast<float>(i / bounds.w)};
            SDL_RenderPoint(renderer, x + bounds.x, y + bounds.y);
        }
    };
    void Canvas::measure(TextManager *textManager, int availableWidth, int availableHeight) {
        // setBounds({.x = bounds.x,
        //    .y = bounds.y,
        //    .w = availableWidth,
        //    .h = availableHeight});
    };
}