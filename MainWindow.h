#pragma once

#include "TextManager.h"
#include <SDL3/SDL.h>
#include "constants.h"
#include <string_view>
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>
#include "Node.h"

std::string stringifyRegisters(char *registers);

class Panel
{
private:
    int w{}, h{}, offsetX{}, offsetY{};
    UI::Node *prevTree{nullptr};

public:
    virtual void onMouseMove(float x, float y);
    Panel(int _w, int _h);
    int getWidth() { return w; };
    int getHeight() { return h; };
    int getOffsetX() { return offsetX; };
    int getOffsetY() { return offsetY; };
    void setOffsetX(int x) { offsetX = x; };
    void setOffsetY(int y) { offsetY = y; };
    virtual void render(SDL_Renderer *renderer, TextManager *textManager);
    virtual std::shared_ptr<UI::Node> getTree();
    virtual void handleScroll(SDL_MouseWheelEvent event);
    void renderPoint(SDL_Renderer *renderer, int x, int y);
};

enum class InstructionType
{
    CLEAR_SCREEN,
    JUMP,
    CALL_SUBROUTINE,
    RETURN_FROM_SUBROUTINE,
    JUMP_EQ_REG_VALUE,
    JUMP_NEQ_REG_VALUE,
    JUMP_EQ_REG_REG,
    JUMP_NEQ_REG_REG,
    SET_REGISTER,
    ADD_TO_REGISTER,
    ADD_TO_INDEX,
    SET_INDEX,
    DRAW,
};

typedef struct Instruction
{
    InstructionType type;
    uint16_t opCode{};
} Instruction;

class Emulator : public Panel
{
public:
    uint16_t programCounter{512};
    char *ram{new char[4096]};
    char registers[16];
    Instruction currentInstruction{};
    uint16_t indexRegister{0};
    char emulatorDisplay[Constants::width * Constants::height];
    SDL_Window *gWindow{nullptr};
    SDL_Renderer *gRenderer{nullptr};
    bool gRunning{true};
    void initialize();
    uint16_t stack[16];
    int8_t stackPointer{-1};
    uint16_t peekCurrentOpCode();
    void loadFile(std::string_view fileName);
    unsigned char peek(char skip = 0);
    Instruction consume();
    void decode(Instruction instruction);
    void clearScreen();
    void render(SDL_Renderer *renderer, TextManager *textManager) override;
    char *getRegisters() { return registers; };
    std::shared_ptr<UI::Node> getTree() override;
    Emulator(int w, int h) : Panel(w, h) {};
};

class Spinner : public UI::Node
{
public:
    void render(SDL_Renderer *renderer, TextManager *textManager, UI::Context ctx) override;
    void measure(TextManager *textManager, float availableWidth, float availableHeight) override;
};

class DebugPanel : public Panel
{
private:
    Emulator *emulator{nullptr};
    std::pair<float, float> mouseCoordinates{};

public:
    void onMouseMove(float x, float y) override;
    UI::Context ctx{};
    void setEmulator(Emulator *_emulator) { emulator = _emulator; };
    Emulator *getEmulator() { return emulator; };
    void render(SDL_Renderer *renderer, TextManager *textManager) override;
    std::shared_ptr<UI::Node> getTree() override;
    void handleScroll(SDL_MouseWheelEvent event) override;
    DebugPanel(int w, int h) : Panel(w, h) {};
};

class Window
{
private:
    DebugPanel debugPanel{Constants::kDebugPanelWidth, Constants::kDebugPanelHeight};
    Emulator emulator{Constants::kScreenWidth, Constants::kScreenHeight};
    std::vector<Panel *> panels{};
    SDL_Window *gWindow{nullptr};
    SDL_Renderer *gRenderer{nullptr};
    TextManager *textManager{nullptr};
    TTF_TextEngine *gTextEngine{nullptr};
    TTF_Font *gFont{nullptr};

public:
    void onMouseMove(float x, float y);
    Window(TextManager *_textManager) : textManager{_textManager} {};
    void addPanel(Panel *panel);
    void cleanup();
    void handleScroll(SDL_MouseWheelEvent event);
    TextManager *getTextManager() { return textManager; };
    int getTotalHeight();
    int getTotalWidth();
    void initialize();
    void render(SDL_Renderer *renderer);
    void renderPoint(int x, int y, Panel &panel);
    void run();
};