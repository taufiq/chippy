#include <iostream>
#include <iterator>
#include <fstream>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <string_view>
#include "constants.h"
#include "MainWindow.h"
#include "GUI.h"
#include <SDL3_ttf/SDL_ttf.h>

TextManager gTextManager{};
Window gWindow{&gTextManager};

int main()
{
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};
    TTF_TextEngine *textEngine{nullptr};

    uint64_t prevTick = 0;
    bool gRunning{true};
    SDL_Event pollEvent;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_CreateWindowAndRenderer("GUI Test", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);
    textEngine = TTF_CreateRendererTextEngine(renderer);
    GUI::InitAll(renderer, textEngine);

    while (gRunning)
    {
        uint64_t now{SDL_GetTicks()};
        if (now - prevTick < 1000.0 / static_cast<float>(Constants::kFps))
        {
            continue;
        }
        prevTick = now;

        while (SDL_PollEvent(&pollEvent))
        {
            switch (pollEvent.type)
            {
            case SDL_EventType::SDL_EVENT_QUIT:
                gRunning = false;
                continue;
            case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
                GUI::SetMousePosition((Vec2f){
                    .x = pollEvent.motion.x,
                    .y = pollEvent.motion.y});
                continue;
            case SDL_EventType::SDL_EVENT_MOUSE_WHEEL:
                GUI::SetScrollDelta((Vec2f){
                    .x = 0.0f,
                    .y = pollEvent.wheel.y,
                });
                continue;
            default:
                continue;
            }
        }
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        GUI::Start(w, h);
        GUI::BeginBox(GUI::Axis::Vertical, 0.5);
        GUI::BeginBox(GUI::Axis::Horizontal, 0.2);
        for (int i = 0; i < 50; i++)
        {
            GUI::Button("Hello");
        }
        GUI::EndBox();

        GUI::BeginBox(0.8);
        GUI::Button("World");
        GUI::EndBox();
        GUI::EndBox();

        GUI::BeginBox(GUI::Axis::Vertical, 0.5);
        GUI::BeginBox(0.5);
        GUI::Button("Goodbye");
        GUI::EndBox();

        GUI::BeginBox(0.5);
        GUI::Button("Bro");
        GUI::EndBox();
        GUI::EndBox();

        GUI::End();

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    // gWindow.initialize();
    // gWindow.run();
    // gWindow.cleanup();
    return 0;
}