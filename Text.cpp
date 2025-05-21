#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace UI
{
    Text::Text(std::string _value)
    {
        value = _value;
    };

    void Text::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        TTF_Text *text = textManager->createText(value);
        TTF_SetTextColor(
            text,
            this->style.textColor.x,
            this->style.textColor.y,
            this->style.textColor.z,
            this->style.textColor.w);
        TTF_DrawRendererText(text, static_cast<float>(this->getBounds().x), static_cast<float>(this->getBounds().y));
    };

    void Text::measure(TextManager *textManager, int availableWidth, int availableHeight)
    {
        TTF_GetStringSizeWrapped(textManager->getFont(), value.c_str(), value.length(), availableWidth, &bounds.w, &bounds.h);
    };
}