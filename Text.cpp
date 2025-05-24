#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL.h>

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
            static_cast<float>(getBounds().x),
            static_cast<float>(getBounds().y),
            static_cast<float>(getBounds().w),
            static_cast<float>(getBounds().h),
        };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
        SDL_RenderRect(renderer, &rect);
        switch (style.alignment)
        {
        case Alignment::LEFT:
            TTF_DrawRendererText(
                text,
                static_cast<float>(getBounds().x),
                static_cast<float>(getBounds().y));
            break;
        case Alignment::CENTER:
            TTF_DrawRendererText(
                text,
                static_cast<float>((getBounds().w - minimumBoundsForText.w) / 2 + getBounds().x),
                static_cast<float>(getBounds().y));
            break;
        case Alignment::RIGHT:
            TTF_DrawRendererText(
                text,
                static_cast<float>(getBounds().w - minimumBoundsForText.w + getBounds().x),
                static_cast<float>(getBounds().y));
            break;
        default:
            break;
        }
    };

    void Text::measure(TextManager *textManager, int availableWidth, int availableHeight)
    {
        TTF_GetStringSizeWrapped(textManager->getFont(), value.c_str(), value.length(), availableWidth, &bounds.w, &bounds.h);
        minimumBoundsForText.w = bounds.w;
        minimumBoundsForText.h = bounds.h;
    };
}