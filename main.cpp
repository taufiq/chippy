#include <iostream>
#include <iterator>
#include <fstream>
#include <SDL.h>
#include <cstdlib>
#include <string_view>

namespace Constants
{
    constexpr int height{32};
    constexpr int width{64};
    constexpr int scale{10};
    constexpr int kScreenWidth{width * scale};
    constexpr int kScreenHeight{height * scale};
    constexpr int kFps{1};
}

void printByte(char byte)
{
    for (char i{0}; i < 8; i++)
    {
        std::cout << (((1u << (7 - i)) & byte) >> (7 - i)) << " ";
    }
    std::cout << std::endl;
}

class Emulator
{
public:
    uint16_t programCounter{512};
    char *ram{new char[4096]};
    char registers[16];
    uint16_t indexRegister{0};
    char emulatorDisplay[Constants::width * Constants::height];
    SDL_Window *gWindow{nullptr};
    SDL_Surface *gSurface{nullptr};
    uint32_t *pixels{nullptr};
    bool gRunning{true};

    void initialize()
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            std::cout << "Failed to initialize video subsystem" << std::endl;
        };

        if (gWindow = SDL_CreateWindow("Window", Constants::kScreenWidth, Constants::kScreenHeight, SDL_WINDOW_RESIZABLE); gWindow == nullptr)
        {
            std::cout << "Failed creating Window" << std::endl;
        }
        gSurface = SDL_GetWindowSurface(gWindow);
        SDL_FillSurfaceRect(gSurface, nullptr, SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA32), NULL, 0, 0, 0));
        pixels = static_cast<uint32_t *>(gSurface->pixels);

        loadFile("ibm.ch8");
    }

    uint16_t peekCurrentInstruction()
    {
        uint16_t instruction{static_cast<uint16_t>((peek() << 8) | peek(1))};
        return instruction;
    }

    void loadFile(std::string_view fileName)
    {
        std::ifstream file{fileName, std::ifstream::binary};
        file.read(&ram[512], 4096 - 512);
    }

    unsigned char peek(char skip = 0)
    {
        return ram[programCounter + skip];
    }

    uint16_t consume()
    {
        uint16_t currentInstruction = peekCurrentInstruction();
        programCounter += 2;
        return currentInstruction;
    }

    void decode(uint16_t instruction)
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
        default:
            break;
        }

        switch (firstNibble)
        {
        case 0x1:
            programCounter = instruction & 0x0FFF;
            SDL_Log("Jump to: %x\n", programCounter);
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
                for (int j = 0; j < 8; j++)
                {
                    emulatorDisplay[(registers[thirdNibble] + i) * Constants::width + registers[secondNibble] + j] = (((1u << (7 - j)) & row) >> (7 - j));
                }
            }
            break;
        default:
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unhandled Instruction: %x", instruction);
            break;
        }
    }

    void clearScreen()
    {
        for (int i = 0; i < Constants::width * Constants::scale; i++)
        {
            for (int j = 0; j < Constants::height * Constants::scale; j++)
            {
                pixels[j * Constants::kScreenWidth + i] = 0;
            }
        }
    }

    void drawScreen()
    {
        for (int i = 0; i < Constants::width; i++)
        {
            for (int j = 0; j < Constants::height; j++)
            {
                if (emulatorDisplay[j * Constants::width + i])
                {
                    paintPixel(i, j, 0xFFFFFFFF);
                }
                else
                {
                    paintPixel(i, j, 0xFF000000);
                }
            }
        }
    }

    void run()
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
            uint16_t currentInstruction = consume();
            decode(currentInstruction);

            drawScreen();
            SDL_UpdateWindowSurface(gWindow);
        }
    }

    void paintPixel(int x, int y, uint32_t color)
    {
        SDL_assert(x < Constants::width);
        SDL_assert(y < Constants::height);
        int endX{(x + 1) * Constants::scale}, endY{(y + 1) * Constants::scale};
        for (int startX{x * Constants::scale}; startX < endX; startX++)
        {
            for (int startY{y * Constants::scale}; startY < endY; startY++)
            {
                pixels[startY * Constants::kScreenWidth + startX] = color;
            }
        }
    }

    void cleanup()
    {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
};

int main()
{
    Emulator emulator{};
    emulator.initialize();
    emulator.run();
    emulator.cleanup();
    return 0;
}