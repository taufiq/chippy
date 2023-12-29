#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GLUT/glut.h>
#include <stdbool.h>
#include <stdint.h>
#include <ft2build.h>
#include FT_FREETYPE_H

FILE *filePointer;
struct stat st;
FT_Library library;
FT_Face face;

#define MILLI_IN_SECOND 1000
#define RENDER_REFRESH_RATE 10
#define INSTRUCTION_CYCLE_RATE 300

#define FILE_NAME "particle.ch8"
#define NO_OF_REGISTERS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 2
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define WINDOW_WIDTH 740
#define WINDOW_HEIGHT 320
#define SCALE 10

#define OP_CLEAR_SCREEN 0x00E0
#define OP_RETURN_FROM_SUBROUTINE 0xEE00

char fonts[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void print_ram(unsigned char *ram, int offset)
{
    for (int i = offset; i < MEMORY_SIZE; i += 2)
    {
        printf("%02x%02x", ram[i], ram[i + 1]);
        if (i % 8 == 0)
        {
            printf("\n");
        }
        else
        {
            printf("\t");
        }
    }
}

void draw(int x, int y, u_int32_t data, uint32_t *pixels)
{
    int xStart = x * SCALE;
    int yStart = y * SCALE;
    int xEnd = xStart + SCALE;
    int yEnd = yStart + SCALE;
    for (int i = xStart; i < xEnd && i < SCREEN_WIDTH; i++)
    {
        for (int j = yStart; j < yEnd && j < SCREEN_HEIGHT; j++)
        {
            pixels[j * SCREEN_WIDTH + i] = data;
        }
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window *win = SDL_CreateWindow("Chippy",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (FT_Init_FreeType(&library))
    {
        printf("Error occcured during font initialization\n");
    }
    if (FT_New_Face(library, "ffaf.ttf", 0, &face))
    {
        printf("Error occured when loading font\n");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        printf("Error while loading char\n");
    }
    SDL_Event e;
    filePointer = fopen(FILE_NAME, "r");
    stat(FILE_NAME, &st);

    // Stores fileSize in bytes
    long long fileSize = st.st_size;
    unsigned char *ram = (unsigned char *)malloc(MEMORY_SIZE);
    unsigned short int indexRegister = 0x0000;
    unsigned short int programCounter = 0x0200;
    unsigned char *registers = (unsigned char *)malloc(NO_OF_REGISTERS);
    unsigned char *stack = (unsigned char *)malloc(sizeof(short int) * STACK_SIZE);
    int stackIndex = -1;

    for (int i = 0; i < NO_OF_REGISTERS; i++)
    {
        registers[i] = 0;
    }

    for (int i = 0; i < fileSize; i++)
    {
        char unsigned byte = fgetc(filePointer);
        ram[0x200 + i] = byte;
    }

    for (int i = 0; i < STACK_SIZE; i++)
    {
        stack[i] = 0x0;
    }

    int i = 0;
    clock_t currentTimeRender = clock();
    clock_t currentTimeInstruction = clock();
    float renderTick = (float)1 / RENDER_REFRESH_RATE * CLOCKS_PER_SEC;
    float instructionTick = (float)1 / INSTRUCTION_CYCLE_RATE * CLOCKS_PER_SEC;

    SDL_Event evt;
    bool running = true;
    char keyInput = 0x0;
    bool isKeyPressed = false;

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Rect screenRectangle = {WINDOW_WIDTH - SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect debuggerRectangle = {0, 0, WINDOW_WIDTH - SCREEN_WIDTH, WINDOW_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int x = 0;
    int y = 0;

    uint32_t *pixels = (uint32_t *)malloc(sizeof(uint32_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
    uint32_t *debuggerPixels = (uint32_t *)malloc(sizeof(uint32_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    {
        pixels[i] = 0x0;
        debuggerPixels[i] = 0xFFFF00FF;
    }
    while (running)
    {
        clock_t now = clock();
        int timePassedRender = now - currentTimeRender;
        if (timePassedRender >= renderTick)
        {
            currentTimeRender = clock();
            SDL_RenderClear(renderer);
            SDL_UpdateTexture(texture, &screenRectangle, (void *)pixels, SCREEN_WIDTH * sizeof(u_int32_t));
            SDL_UpdateTexture(texture, &debuggerRectangle, (void *)debuggerPixels, (WINDOW_WIDTH - SCREEN_WIDTH) * sizeof(u_int32_t));
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        int timePassedInstruction = now - currentTimeInstruction;
        if (timePassedInstruction < instructionTick)
        {
            continue;
        }

        currentTimeInstruction = clock();

        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                isKeyPressed = true;
                switch (evt.key.keysym.sym)
                {
                case SDLK_1:
                    keyInput = 0x1;
                    break;
                case SDLK_2:
                    keyInput = 0x2;
                    break;
                case SDLK_3:
                    keyInput = 0x3;
                    break;
                case SDLK_4:
                    keyInput = 0xC;
                    break;
                case SDLK_q:
                    keyInput = 0x4;
                    break;
                case SDLK_w:
                    keyInput = 0x5;
                    break;
                case SDLK_e:
                    keyInput = 0x6;
                    break;
                case SDLK_r:
                    keyInput = 0xD;
                    break;
                case SDLK_a:
                    keyInput = 0x7;
                    break;
                case SDLK_s:
                    keyInput = 0x8;
                    break;
                case SDLK_d:
                    keyInput = 0x9;
                    break;
                case SDLK_f:
                    keyInput = 0xE;
                    break;
                case SDLK_z:
                    keyInput = 0xA;
                    break;
                case SDLK_x:
                    keyInput = 0x0;
                    break;
                case SDLK_c:
                    keyInput = 0xB;
                    break;
                case SDLK_v:
                    keyInput = 0xF;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                isKeyPressed = false;
                break;
            default:
                break;
            }
        }
        if (!running)
        {
            break;
        }

        unsigned char firstByte = ram[programCounter];
        unsigned char secondByte = ram[programCounter + 1];

        unsigned char opCode = (firstByte >> 4) & 0x0F;
        unsigned char X = firstByte & 0x0F;
        unsigned char Y = (secondByte >> 4) & 0x0F;

        unsigned char N = secondByte & 0x0F;
        unsigned char NN = secondByte;
        unsigned short int NNN = ((firstByte & 0x0F) << 8) + secondByte;

        unsigned short int instruction = (firstByte << 8) + secondByte;

        programCounter += 2;
        // printf("%x\n", instruction);

        switch (opCode)
        {
        case 0x0:
            if (instruction == OP_CLEAR_SCREEN)
            {
                for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
                {
                    pixels[i] = 0x0;
                }
            }
            else if (instruction == OP_RETURN_FROM_SUBROUTINE)
            {
                unsigned char returnToAddress = stack[stackIndex];
                stackIndex -= 1;
                programCounter = returnToAddress;
                // TODO: Test whether subroutines work
            }
            break;
        case 0x1: // Jump PC to NNN
            programCounter = NNN;
            break;
        case 0x2: // Subroutine
            stackIndex += 1;
            stack[stackIndex] = programCounter;
            programCounter = NNN;
            break;
        case 0x3:
            if (registers[X] == NN)
            {
                programCounter += 2;
            }
            break;
        case 0x4:
            if (registers[X] != NN)
            {
                programCounter += 2;
            }
            break;
        case 0x5:
            if (registers[X] == registers[Y])
            {
                programCounter += 2;
            }
            break;
        case 0x6:
            registers[X] = NN;
            break;
        case 0x7:
            registers[X] += NN;
            break;
        case 0x8:
            switch (N)
            {
            case 0x0:
                registers[X] = registers[Y];
                break;
            case 0x1:
                registers[X] = registers[X] | registers[Y];
                break;
            case 0x2:
                registers[X] = registers[X] & registers[Y];
                break;
            case 0x3:
                registers[X] = registers[X] ^ registers[Y];
                break;
            case 0x4: // Not sure if this detects overflow
                if ((registers[X] >> 7) != (registers[X] + registers[Y]) >> 7)
                {
                    registers[0xF] = 1;
                }
                registers[X] = registers[X] + registers[Y];
                break;
            case 0x5:
                if (registers[X] > registers[Y])
                {
                    registers[0xF] = 1;
                }
                registers[X] = registers[X] - registers[Y];
                break;
            case 0x7:
                if (registers[Y] > registers[X])
                {
                    registers[0xF] = 1;
                }
                registers[X] = registers[Y] - registers[X];
                break;
            case 0x6: // Shift Right - Ambiguous
                registers[0xF] = 0x1 & registers[X];
                registers[X] >>= 1;
                break;
            case 0xE: // Shift Left - Ambiguous
                registers[0xF] = (0x80 & registers[X]) >> 7;
                registers[X] <<= 1;
                break;
            default:
                break;
            }
            break;
        case 0x9:
            if (registers[X] != registers[Y])
            {
                programCounter += 2;
            }
            break;
        case 0xA:
            indexRegister = NNN;
            break;
        case 0xC: // TODO: add randomization
            registers[X] = rand() & NN;
            break;
        case 0xD:
        {
            int initX = registers[X];
            int initY = registers[Y];
            int height = N;
            int y = initY;
            for (int offset = 0; offset < height; offset++)
            {
                unsigned char row = ram[indexRegister + offset];
                for (int x = initX; x < initX + 8; x++)
                {
                    unsigned char bit = row & 0x80;
                    row <<= 1;
                    if (bit && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
                    {
                        draw(x, y, 0xffffffff, pixels);
                    }
                }
                y += 1;
            }
        }
        break;
        case 0xE:
            switch (secondByte)
            {
            case 0x9E:
                if (isKeyPressed && registers[X] == keyInput)
                {
                    programCounter += 2;
                }
                break;
            case 0xA1:
                if (isKeyPressed && registers[X] != keyInput)
                {
                    programCounter += 2;
                }
                break;
            }
        case 0xF:
            switch (secondByte)
            {
            case 0x0A:
                if (isKeyPressed)
                {
                    registers[X] = keyInput;
                }
                else
                {
                    programCounter -= 2;
                }
                break;
            case 0x29:
                break;
            }
        default:
            break;
        }
        // printf("programCounter %x\n", programCounter);
    }
    free(ram);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(win);
    SDL_Quit();
    // printf("%x", *indexPointer);
    // print_ram(ram, 0x200);
    return 0;
}