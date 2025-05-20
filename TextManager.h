#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL.h>
#include <string>

class TextManager
{
private:
    TTF_TextEngine *textEngine{nullptr};
    TTF_Font *gFont{nullptr};

public:
    void initialize(SDL_Renderer *renderer);
    TTF_Text *createText(std::string text);
    TTF_Font *getFont() { return gFont; };
    void cleanup();
};