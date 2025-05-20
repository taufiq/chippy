#include <SDL3_ttf/SDL_ttf.h>
#include <SDL.h>
#include <string>
#include "TextManager.h"

void TextManager::initialize(SDL_Renderer *renderer)
{

    textEngine = TTF_CreateRendererTextEngine(renderer);
    gFont = TTF_OpenFont("fonts/font.ttf", 20);
}

void TextManager::cleanup()
{
    TTF_CloseFont(gFont);
}

TTF_Text *TextManager::createText(std::string text)
{
    return TTF_CreateText(textEngine, gFont, text.c_str(), text.length());
}