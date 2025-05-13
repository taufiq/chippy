#include <SDL.h>
#include "constants.h"
#include <string_view>
#include <vector>
#pragma once

class Panel
{
private:
    int w{}, h{};

public:
    Panel(int _w, int _h);
    int getWidth();
    virtual void draw(SDL_Renderer *renderer);
    void drawPoint(SDL_Renderer *renderer, int x, int y, int color);
};

class Emulator : public Panel
{
public:
    uint16_t programCounter{512};
    char *ram{new char[4096]};
    char registers[16];
    uint16_t indexRegister{0};
    char emulatorDisplay[Constants::width * Constants::height];
    SDL_Window *gWindow{nullptr};
    SDL_Renderer *gRenderer{nullptr};
    bool gRunning{true};
    void initialize();
    uint16_t stack[16];
    int8_t stackPointer{-1};
    uint16_t peekCurrentInstruction();
    void loadFile(std::string_view fileName);
    unsigned char peek(char skip = 0);
    uint16_t consume();
    void decode(uint16_t instruction);
    void clearScreen();
    void drawScreen();
    void paintPixel(int x, int y, uint32_t color);
    void draw(SDL_Renderer *renderer) override;
    Emulator(int w, int h) : Panel(w, h) {};
};
class Window
{
private:
    Panel debugPanel{Constants::kDebugPanelWidth, Constants::kDebugPanelHeight};
    Emulator emulator{Constants::kScreenWidth, Constants::kScreenHeight};
    std::vector<Panel> panels{debugPanel, emulator};
    SDL_Window *gWindow{nullptr};
    SDL_Renderer *gRenderer{nullptr};

public:
    Window();
    void initialize();
    void cleanup();
    void draw(SDL_Renderer *renderer);
    int getTotalWidth();
    int getTotalHeight();
    void run();
};