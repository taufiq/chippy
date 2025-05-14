#include <SDL.h>
#include "constants.h"
#include <string_view>
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>
#pragma once

class Panel
{
private:
    int w{}, h{}, offsetX{}, offsetY{};

public:
    Panel(int _w, int _h);
    int getWidth() { return w; };
    int getOffsetX() { return offsetX; };
    int getOffsetY() { return offsetY; };
    void setOffsetX(int x) { offsetX = x; };
    virtual void render(SDL_Renderer *renderer);
    void renderPoint(SDL_Renderer *renderer, int x, int y);
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
    void render(SDL_Renderer *renderer) override;
    Emulator(int w, int h) : Panel(w, h) {};
};
class TextManager
{
private:
    TTF_TextEngine *textEngine{nullptr};
    TTF_Font *gFont{nullptr};

public:
    void initialize(SDL_Renderer *renderer);
    TTF_Text *createText(std::string text);
    void cleanup();
};
class Window
{
private:
    Panel debugPanel{Constants::kDebugPanelWidth, Constants::kDebugPanelHeight};
    Emulator emulator{Constants::kScreenWidth, Constants::kScreenHeight};
    std::vector<Panel *> panels{};
    SDL_Window *gWindow{nullptr};
    SDL_Renderer *gRenderer{nullptr};
    TextManager *textManager{nullptr};
    TTF_TextEngine *gTextEngine{nullptr};
    TTF_Font *gFont{nullptr};

public:
    Window(TextManager *_textManager) : textManager{_textManager} {};
    void addPanel(Panel *panel);
    void cleanup();
    TextManager *getTextManager() { return textManager; };
    int getTotalHeight();
    int getTotalWidth();
    void initialize();
    void render(SDL_Renderer *renderer);
    void renderPoint(int x, int y, Panel &panel);
    void run();
};