#include "Window.h"
#include <SDL.h>
#include "constants.h"
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string_view>
#include <SDL3_ttf/SDL_ttf.h>

int gRunning{true};

void printByte(char byte)
{
    for (char i{0}; i < 8; i++)
    {
        std::cout << (((1u << (7 - i)) & byte) >> (7 - i)) << " ";
    }
    std::cout << std::endl;
}

void Window::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Failed to initialize video subsystem" << std::endl;
    };

    if (SDL_CreateWindowAndRenderer("Window", Constants::kScreenWidth, Constants::kScreenHeight, SDL_WINDOW_RESIZABLE, &gWindow, &gRenderer); gWindow == nullptr)
    {
        std::cout << "Failed creating Window" << std::endl;
    }

    Window::addPanel(&debugPanel);
    Window::addPanel(&emulator);

    emulator.initialize();
    textManager->initialize(gRenderer);

    SDL_SetWindowSize(gWindow, Window::getTotalWidth(), Window::getTotalHeight());
}

void Window::render(SDL_Renderer *renderer)
{
    for (auto panel : panels)
    {
        panel->render(renderer);
    }
}

int Window::getTotalWidth()
{
    int width{0};
    for (auto p : panels)
    {
        width += p->getWidth();
    }
    return width;
}

int Window::getTotalHeight()
{
    return Constants::kScreenHeight;
}

void Window::run()
{
    uint64_t prevTick = 0;
    SDL_Event pollEvent;

    while (gRunning)
    {
        uint64_t now{SDL_GetTicks()};
        if (now - prevTick < 1000.0 / Constants::kFps)
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
                break;
            }
        }
        uint16_t currentInstruction = emulator.consume();
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        emulator.decode(currentInstruction);
        render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }
}

Panel::Panel(int _w, int _h) : w{_w}, h{_h} {};

void Emulator::initialize()
{
    loadFile("roms/chipper.ch8");
}

uint16_t Emulator::peekCurrentInstruction()
{
    uint16_t instruction{static_cast<uint16_t>((peek() << 8) | peek(1))};
    return instruction;
}

void Emulator::loadFile(std::string_view fileName)
{
    std::ifstream file{fileName, std::ifstream::binary};
    file.read(&ram[512], 4096 - 512);
}

unsigned char Emulator::peek(char skip)
{
    return ram[programCounter + skip];
}

uint16_t Emulator::consume()
{
    uint16_t currentInstruction = peekCurrentInstruction();
    programCounter += 2;
    return currentInstruction;
}

void Emulator::decode(uint16_t instruction)
{
    SDL_Log("Current instruction: %x\n", instruction);
    unsigned char firstNibble{static_cast<unsigned char>((instruction & 0xF000) >> 12)},
        secondNibble{static_cast<unsigned char>((instruction & 0x0F00) >> 8)},
        thirdNibble{static_cast<unsigned char>((instruction & 0x00F0) >> 4)},
        fourthNibble{static_cast<unsigned char>(0x000F & instruction)};
    char previousValue = registers[secondNibble];

    switch (instruction)
    {
    case 0x00E0:
        clearScreen();
        return;
    case 0x00EE:
        SDL_Log("Jump to: %x\n", stack[stackPointer]);
        programCounter = stack[stackPointer--];
        break;
    default:
        break;
    }

    switch (firstNibble)
    {
    case 0x1:
        programCounter = instruction & 0x0FFF;
        SDL_Log("Jump to: %x\n", programCounter);
        break;
    case 0x2:
        stack[++stackPointer] = programCounter;
        SDL_Log("jump to: %x\n", instruction & 0x0FFF);
        programCounter = instruction & 0x0FFF;
        break;
    case 0x6:
        registers[secondNibble] = instruction & 0x00FF;
        SDL_Log("Setting register V%x to %x\n", secondNibble, registers[secondNibble]);
        break;
    case 0x7:
        registers[secondNibble] += instruction & 0x00FF;
        SDL_Log("Adding register V%x from %x to %x\n", secondNibble, previousValue, registers[secondNibble]);
        break;
    case 0xA:
        indexRegister = instruction & 0x0FFF;
        SDL_Log("Setting index register to %x\n", indexRegister);
        break;
    case 0xD:
        SDL_Log("Draw X->V%d:%x\n\tY->V%d:%x", secondNibble, registers[secondNibble], thirdNibble, registers[thirdNibble]);
        SDL_Log("\n%d Sprites Tall\n", fourthNibble);
        for (unsigned char i = 0; i < fourthNibble; i++)
        {
            unsigned char row = ram[indexRegister + i];
            printByte(row);
            for (int j = 0; j < 8; j++)
            {
                emulatorDisplay[(registers[thirdNibble] + i) * Constants::width + registers[secondNibble] + j] = (((1u << (7 - j)) & row) >> (7 - j));
            }
        }
        break;
    case 0x3:
        if (registers[secondNibble] == (0x00FF & instruction))
        {
            SDL_Log("Checking if V%d=[%x] == %x: Yes.. Skipping", secondNibble, registers[secondNibble], (0x00FF & instruction));
            programCounter += 2;
        }
        else
        {
            SDL_Log("Checking if V%d=[%x] == %x: No.. Not Skipping", secondNibble, registers[secondNibble], (0x00FF & instruction));
        }
    case 0x4:
        if (registers[secondNibble] != (0x00FF & instruction))
        {
            SDL_Log("Checking if V%d=[%x] != %x Yes.. Skipping", secondNibble, registers[secondNibble], (0x00FF & instruction));
            programCounter += 2;
        }
        else
        {
            SDL_Log("Checking if V%d=[%x] != %x No.. Not Skipping", secondNibble, registers[secondNibble], (0x00FF & instruction));
        }
        break;
    case 0x5:
        if (registers[secondNibble] == registers[thirdNibble])
        {
            SDL_Log("Checking if V%d=[%x] == V%d=[%x] Yes.. Skipping", secondNibble, registers[secondNibble], thirdNibble, registers[thirdNibble]);
            programCounter += 2;
        }
        else
        {
            SDL_Log("Checking if V%d=[%x] == V%d=[%x] No.. Not Skipping", secondNibble, registers[secondNibble], thirdNibble, registers[thirdNibble]);
        }
        break;
    case 0x9:
        if (registers[secondNibble] != registers[thirdNibble])
        {
            SDL_Log("Checking if V%d=[%x] != V%d=[%x] Yes.. Skipping", secondNibble, registers[secondNibble], thirdNibble, registers[thirdNibble]);
            programCounter += 2;
        }
        else
        {
            SDL_Log("Checking if V%d=[%x] != V%d=[%x] No.. Not Skipping", secondNibble, registers[secondNibble], thirdNibble, registers[thirdNibble]);
        }
        break;
    case 0xF:
        if ((instruction & 0x00FF) == 0x001E)
        {
            indexRegister += registers[secondNibble];
        }
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unhandled Instruction: %x", instruction);
        break;
    }
}

void Emulator::clearScreen()
{
    for (int i = 0; i < Constants::width; i++)
    {
        for (int j = 0; j < Constants::height; j++)
        {
            emulatorDisplay[j * Constants::width + i] = 0;
        }
    }
}

void Emulator::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int x{0}; x < Constants::width; x++)
    {
        for (int y{0}; y < Constants::height; y++)
        {
            if (emulatorDisplay[y * Constants::width + x])
            {
                for (int startX{x * Constants::scale}; startX < (x + 1) * Constants::scale; startX++)
                {
                    for (int startY{y * Constants::scale}; startY < (y + 1) * Constants::scale; startY++)
                    {
                        renderPoint(renderer, startX, startY);
                    }
                }
            }
        }
    }
}

void Panel::renderPoint(SDL_Renderer *renderer, int x, int y)
{
    SDL_RenderPoint(renderer, offsetX + x, offsetY + y);
}

void Window::cleanup()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    textManager->cleanup();
    SDL_Quit();
}

void Panel::render(SDL_Renderer *renderer) {}

void Window::addPanel(Panel *panel)
{
    panel->setOffsetX(Window::getTotalWidth());
    panels.push_back(panel);
}

void TextManager::initialize(SDL_Renderer *renderer)
{

    textEngine = TTF_CreateRendererTextEngine(renderer);
    gFont = TTF_OpenFont("fonts/font.ttf", 8);
}

void TextManager::cleanup()
{
    TTF_CloseFont(gFont);
}

TTF_Text *TextManager::createText(std::string text)
{
    return TTF_CreateText(textEngine, gFont, text.c_str(), text.length());
}
