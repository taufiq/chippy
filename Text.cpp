#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace UI
{
    Text::Text(std::optional<uint64_t> _backgroundColor,
               std::optional<uint64_t> _textColor,
               std::string _value)
    {
        if (_backgroundColor)
            backgroundColor = _backgroundColor.value();
        if (_textColor)
            textColor = _textColor.value();
        value = _value;
    };

    void Text::render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx)
    {
        TTF_Text *text = textManager->createText(value);
        TTF_SetTextColor(text, 255, 0, 0, 255);
        TTF_DrawRendererText(text, static_cast<float>(this->getBounds().x), static_cast<float>(this->getBounds().y));
        // TTF_DrawRendererText(text, 10.0f, 10.0f);
    };

    void Text::measure(TextManager *textManager, int availableWidth, int availableHeight)
    {
        TTF_GetStringSizeWrapped(textManager->getFont(), value.c_str(), value.length(), availableWidth, &bounds.w, &bounds.h);
    };
}