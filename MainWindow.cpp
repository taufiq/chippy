#include <math.h>
#include "MainWindow.h"
#include "Canvas.h"
#include "Box.h"
#include "Text.h"
#include <SDL3/SDL.h>
#include "constants.h"
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string_view>
#include <sstream>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextManager.h"
#include <random>

int gRunning{true};

void printByte(char byte)
{
    for (char i{0}; i < 8; i++)
    {
        std::cout << (((1u << (7 - i)) & byte) >> (7 - i)) << " ";
    }
    std::cout << std::endl;
}

std::string stringifyRegisters(char *registers)
{
    std::stringstream ss;
    for (int i{0}; i < 16; i++)
    {
        ss << "V" << i << ":" << static_cast<int>(registers[i]) << "\n";
    }
    return ss.str();
}

void Window::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Failed to initialize video subsystem" << std::endl;
    };
    if (TTF_Init() == false)
    {
        SDL_Log("Failed to Initialize TTF!");
    };

    if (SDL_CreateWindowAndRenderer("Window", Constants::kScreenWidth, Constants::kScreenHeight, SDL_WINDOW_RESIZABLE, &gWindow, &gRenderer); gWindow == nullptr)
    {
        std::cout << "Failed creating Window" << std::endl;
    }

    Window::addPanel(&debugPanel);
    Window::addPanel(&emulator);

    emulator.initialize();

    debugPanel.setEmulator(&emulator);
    textManager->initialize(gRenderer);

    SDL_SetWindowSize(gWindow, Window::getTotalWidth(), Window::getTotalHeight());
}

void Window::render(SDL_Renderer *renderer)
{
    float result{};
    if (debugPanel.initialForce != 0)
    {
        auto roundingFunction = debugPanel.initialForce >= 0 ? std::floorf : std::ceilf;
        debugPanel.initialForce = roundingFunction(debugPanel.initialForce * 10) / 11.4f;
        debugPanel.scrollY += debugPanel.initialForce;
    }

    for (auto panel : panels)
    {
        panel->render(renderer, textManager);
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
        if (now - prevTick < 1000.0 / static_cast<float>(Constants::kFps))
        {
            continue;
        }
        prevTick = now;

        while (SDL_PollEvent(&pollEvent))
        {
            // auto initialForce = pollEvent.wheel.y;
            // auto acceleration = -pollEvent.wheel.y;
            switch (pollEvent.type)
            {
            case SDL_EventType::SDL_EVENT_QUIT:
                gRunning = false;
                continue;
            case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
                onMouseMove(pollEvent.motion.x, pollEvent.motion.y);
                continue;
            case SDL_EventType::SDL_EVENT_MOUSE_WHEEL:
                debugPanel.initialForce = Constants::kMouseSensitivity * pollEvent.wheel.y;
            default:
                continue;
            }
        }
        Instruction currentInstruction = emulator.consume();
        emulator.currentInstruction = currentInstruction;
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        emulator.decode(currentInstruction);
        render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }
}

void Window::onMouseMove(float x, float y)
{
    for (auto &panel : panels)
    {
        if (x >= panel->getOffsetX() && y >= panel->getOffsetY() && x < panel->getOffsetX() + panel->getWidth() && y < panel->getOffsetY() + panel->getHeight())
        {
            panel->onMouseMove(x, y);
        }
    }
}

Panel::Panel(int _w, int _h) : w{_w}, h{_h} {};

void Emulator::initialize()
{
    loadFile("roms/chipper.ch8");
}

uint16_t Emulator::peekCurrentOpCode()
{
    uint16_t opCode{static_cast<uint16_t>((peek() << 8) | peek(1))};
    return opCode;
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

Instruction Emulator::consume()
{
    uint16_t opCode = peekCurrentOpCode();
    programCounter += 2;
    unsigned char firstNibble{static_cast<unsigned char>((opCode & 0xF000) >> 12)},
        secondNibble{static_cast<unsigned char>((opCode & 0x0F00) >> 8)},
        thirdNibble{static_cast<unsigned char>((opCode & 0x00F0) >> 4)},
        fourthNibble{static_cast<unsigned char>(0x000F & opCode)};
    InstructionType type{};
    switch (opCode)
    {
    case 0x00E0:
        type = InstructionType::CLEAR_SCREEN;
        break;
    case 0x00EE:
        type = InstructionType::RETURN_FROM_SUBROUTINE;
        break;
    default:
        break;
    }
    switch (firstNibble)
    {
    case 0x1:
        type = InstructionType::JUMP;
        break;
    case 0x2:
        type = InstructionType::CALL_SUBROUTINE;
        break;
    case 0x6:
        type = InstructionType::SET_REGISTER;
        break;
    case 0x7:
        type = InstructionType::ADD_TO_REGISTER;
        break;
    case 0xA:
        type = InstructionType::SET_INDEX;
        break;
    case 0xD:
        type = InstructionType::DRAW;
        break;
    case 0x3:
        type = InstructionType::JUMP_EQ_REG_VALUE;
        break;
    case 0x4:
        type = InstructionType::JUMP_NEQ_REG_VALUE;
        break;
    case 0x5:
        type = InstructionType::JUMP_EQ_REG_REG;
        break;
    case 0x9:
        type = InstructionType::JUMP_NEQ_REG_REG;
        break;
    case 0xF:
        if ((opCode & 0x00FF) == 0x001E)
        {
            type = InstructionType::ADD_TO_INDEX;
        }
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unhandled Instruction: %x", opCode);
        break;
    }
    return Instruction{type, opCode};
}

void Emulator::decode(Instruction instruction)
{
    SDL_Log("Current instruction: %x\n", instruction.opCode);
    uint16_t opCode = instruction.opCode;
    unsigned char firstNibble{static_cast<unsigned char>((opCode & 0xF000) >> 12)},
        secondNibble{static_cast<unsigned char>((opCode & 0x0F00) >> 8)},
        thirdNibble{static_cast<unsigned char>((opCode & 0x00F0) >> 4)},
        fourthNibble{static_cast<unsigned char>(0x000F & opCode)};
    char previousValue = registers[secondNibble];

    switch (instruction.type)
    {
    case InstructionType::CLEAR_SCREEN:
        clearScreen();
        return;
    case InstructionType::RETURN_FROM_SUBROUTINE:
        SDL_Log("Jump to: %x\n", stack[stackPointer]);
        programCounter = stack[stackPointer--];
        break;
    case InstructionType::JUMP:
        programCounter = opCode & 0x0FFF;
        SDL_Log("Jump to: %x\n", programCounter);
        break;
    case InstructionType::CALL_SUBROUTINE:
        stack[++stackPointer] = programCounter;
        SDL_Log("jump to: %x\n", opCode & 0x0FFF);
        programCounter = opCode & 0x0FFF;
        break;
    case InstructionType::SET_REGISTER:
        registers[secondNibble] = opCode & 0x00FF;
        SDL_Log("Setting register V%x to %x\n", secondNibble, registers[secondNibble]);
        break;
    case InstructionType::ADD_TO_REGISTER:
        registers[secondNibble] += opCode & 0x00FF;
        SDL_Log("Adding register V%x from %x to %x\n", secondNibble, previousValue, registers[secondNibble]);
        break;
    case InstructionType::SET_INDEX:
        indexRegister = opCode & 0x0FFF;
        SDL_Log("Setting index register to %x\n", indexRegister);
        break;
    case InstructionType::DRAW:
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
    case InstructionType::JUMP_EQ_REG_VALUE:
        if (registers[secondNibble] == (0x00FF & opCode))
        {
            SDL_Log("Checking if V%d=[%x] == %x: Yes.. Skipping", secondNibble, registers[secondNibble], (0x00FF & opCode));
            programCounter += 2;
        }
        else
        {
            SDL_Log("Checking if V%d=[%x] == %x: No.. Not Skipping", secondNibble, registers[secondNibble], (0x00FF & opCode));
        }
    case InstructionType::JUMP_NEQ_REG_VALUE:
        if (registers[secondNibble] != (0x00FF & opCode))
        {
            SDL_Log("Checking if V%d=[%x] != %x Yes.. Skipping", secondNibble, registers[secondNibble], (0x00FF & opCode));
            programCounter += 2;
        }
        else
        {
            SDL_Log("Checking if V%d=[%x] != %x No.. Not Skipping", secondNibble, registers[secondNibble], (0x00FF & opCode));
        }
        break;
    case InstructionType::JUMP_EQ_REG_REG:
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
    case InstructionType::JUMP_NEQ_REG_REG:
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
    case InstructionType::ADD_TO_INDEX:
        if ((opCode & 0x00FF) == 0x001E)
        {
            indexRegister += registers[secondNibble];
        }
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unhandled Instruction: %x", opCode);
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

void Emulator::render(SDL_Renderer *renderer, TextManager *textManager)
{
    std::shared_ptr<UI::Node> treeToRender = getTree();
    UI::Context ctx{};
    treeToRender->measure(textManager, this->getWidth(), this->getHeight());
    treeToRender->render(renderer, textManager, &ctx);
}

void Panel::renderPoint(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPoint(renderer, offsetX + x, offsetY + y);
}

void Window::cleanup()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    textManager->cleanup();
    SDL_Quit();
}

void Panel::render(SDL_Renderer *renderer, TextManager *textManager) {}

void Window::addPanel(Panel *panel)
{
    panel->setOffsetX(Window::getTotalWidth());
    panels.push_back(panel);
}

void DebugPanel::render(SDL_Renderer *renderer, TextManager *textManager)
{
    static std::shared_ptr<UI::Node> tree{nullptr};
    if (!tree)
    {
        tree = getTree();
    }
    // 2. How to craft the measure function to save information
    tree->measure(textManager, this->getWidth(), this->getHeight());
    UI::Context ctx{};
    // TODO: Terrible way of handling, maybe should convert DebugPanel into a UI element as well.
    tree->onMouseMove(mouseCoordinates.first, mouseCoordinates.second);
    tree->render(renderer, textManager, &ctx);
}

/**
 * RegisterText {
 *  int index;
 *  std::string_view getString() {
 *      return string;
 *  }
 * }
 */
// This recreates the entire UI over and over again
// Is there a way to separate it?
// 1. Declare how I want it to look like
// 2. See if it differs:
//  a. by state value?
//  b. by children?

std::shared_ptr<UI::Node> DebugPanel::getTree()
{
    std::shared_ptr<UI::Box> box = std::make_shared<UI::Box>();

    box->setLayoutMode(UI::LayoutMode::HORIZONTAL);
    box->setBounds({static_cast<float>(getOffsetX()),
                    static_cast<float>(getOffsetY()),
                    0.0f,
                    0.0f});
    box->style.paddingX = 16;
    std::unique_ptr<UI::Box> innerBox{std::make_unique<UI::Box>()};

    for (int i = 0; i < 16; i++)
    {
        std::string registerValue{};
        // bind Text(text, format, value)
        // textBox.bind(this->getEmulator()->registers[i], std::format("V{}: \{\}", i));
        // Pass in address of string?
        // Pass in a new type that when I call get
        std::unique_ptr<UI::Text> textBox = std::make_unique<UI::Text>([this, i]()
                                                                       { return std::format("V{}: {}", i, static_cast<int>(this->getEmulator()->registers[i])); });
        innerBox->addChild(std::move(textBox));

        if (innerBox->getChildren().size() == 3)
        {
            box->addChild(std::move(innerBox));
            innerBox = std::make_unique<UI::Box>();
        }
    }
    if (innerBox->getChildren().size())
    {
        box->addChild(std::move(innerBox));
    }
    std::unique_ptr<UI::Text> instructionText = std::make_unique<UI::Text>(
        [this]()
        { return std::format("{:x}", this->getEmulator()->currentInstruction.opCode); });
    box->addChild(std::move(instructionText));

    return box;
}

std::shared_ptr<UI::Node> Emulator::getTree()
{
    std::shared_ptr<UI::Canvas> canvas = std::make_shared<UI::Canvas>(
        static_cast<float>(Constants::width * Constants::scale),
        static_cast<float>(Constants::height * Constants::scale));
    canvas->setBounds({.x = static_cast<float>(getOffsetX()),
                       .y = static_cast<float>(getOffsetY()),
                       .w = static_cast<float>(Constants::width * Constants::scale),
                       .h = static_cast<float>(Constants::height * Constants::scale)});

    for (int x{0}; x < Constants::width; x++)
    {
        for (int y{0}; y < Constants::height; y++)
        {
            if (emulatorDisplay[y * Constants::width + x])
            {
                Vec4 randomVector{rand() % 255, rand() % 255, rand() % 255, 255};
                Vec4 whiteVector{255, 255, 255, 255};
                Vec4 vector = whiteVector;
                for (int startX{x * Constants::scale}; startX < (x + 1) * Constants::scale; startX++)
                {

                    for (int startY{y * Constants::scale}; startY < (y + 1) * Constants::scale; startY++)
                    {
                        canvas->pixels[startY * (Constants::width * Constants::scale) + startX] = (Vec4){
                            .x = vector.x,
                            .y = vector.y,
                            .z = vector.z,
                            .w = vector.w,
                        };
                    }
                }
            }
        }
    }
    return canvas;
}
void DebugPanel::onMouseMove(float x, float y)
{
    mouseCoordinates = std::make_pair(x, y);
};

std::shared_ptr<UI::Node> Panel::getTree()
{
}

void Panel::onMouseMove(float x, float y) {}