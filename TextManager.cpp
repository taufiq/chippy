#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <SDL3/SDL.h>
#include <string>
#include "TextManager.h"

void TextManager::initialize(SDL_Renderer *renderer)
{

    std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
    SDL_Log("%s", cwd.string().c_str());

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