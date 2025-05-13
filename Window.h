#include <SDL.h>
#include "constants.h"
#pragma once

class Panel
{
private:
    SDL_Rect frameRectangle{};
    SDL_Surface *surface;

public:
    Panel(int x, int y, int w, int h);
    void draw();
};

class Window
{
private:
    Panel debugPanel{0, 0, Constants::kDebugPanelWidth, Constants::kDebugPanelHeight};
    Panel gamePanel{Constants::kDebugPanelWidth, 0, Constants::kScreenWidth, Constants::kScreenHeight};

public:
    Window();
};