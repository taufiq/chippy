#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

namespace UI
{
    Text::Text(std::string _value) : value{_value}
    {
        style.paddingX = 4;
        style.paddingY = 2;
    };

    void Text::setBounds(Bounds _bounds)
    {
        Node::setBounds(_bounds);
    };

    void Text::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        TTF_Text *text = textManager->createText(value);
        TTF_SetTextColor(
            text,
            style.textColor.x,
            style.textColor.y,
            style.textColor.z,
            style.textColor.w);
        SDL_FRect rect{
            getBounds().x,
            getBounds().y,
            getBounds().w,
            getBounds().h,
        };
        SDL_SetRenderDrawColor(renderer, 0xFF, isMouseOver ? 0xFF : 0, 0, 0xFF);
        SDL_RenderRect(renderer, &rect);
        switch (style.alignment)
        {
        case Alignment::LEFT:
            TTF_DrawRendererText(
                text,
                getBounds().x,
                getBounds().y);
            break;
        case Alignment::CENTER:
            TTF_DrawRendererText(
                text,
                (getBounds().w - minimumBoundsForText.w) / 2 + getBounds().x,
                getBounds().y);
            break;
        case Alignment::RIGHT:
            TTF_DrawRendererText(
                text,
                getBounds().w - minimumBoundsForText.w + getBounds().x,
                getBounds().y);
            break;
        default:
            break;
        }
    };

    void Text::measure(TextManager *textManager, float availableWidth, float availableHeight)
    {
        int w, h;
        TTF_GetStringSizeWrapped(textManager->getFont(), value.c_str(), value.length(), availableWidth, &w, &h);
        bounds.w = w;
        bounds.h = h;
        minimumBoundsForText.w = bounds.w;
        minimumBoundsForText.h = bounds.h;
    };

    void Text::onMouseMove(float x, float y)
    {
        SDL_Log("Mouse in view of Text: %s (%f, %f) text = (%f, %f) %d", value.c_str(), x, y, bounds.x, bounds.y, isMouseOver);
    }

}