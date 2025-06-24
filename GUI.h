#pragma once

#include "Vec.h"
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define CONTEXT_STACK_SIZE 10

namespace GUI
{
    typedef enum Axis
    {
        Horizontal,
        Vertical
    } Axis;

    typedef struct WindowContext
    {
        Vec2f position{};
        Vec2f size{};
        Vec2f cursor{};
        Axis axis{Axis::Horizontal};
    } WindowContext;

    typedef struct Button
    {
    } UIButton;

    typedef struct Text
    {
    } UIText;

    typedef struct WindowManager
    {
        WindowContext *stack{nullptr};
        uint16_t stackIndex{0};

        SDL_Renderer *renderer;
        TTF_TextEngine *textEngine;
        TTF_Font *font;
        std::vector<UIButton> buttons;
        std::vector<UIText> texts;
    } WindowManager;

    void InitAll(SDL_Renderer *renderer, TTF_TextEngine *textEngine);

    void Start(int width, int height);
    void End();

    WindowManager &GetManager();
    WindowContext &GetContext();

    void PushContext();
    void PopContext();
    void AdvanceCursor(Vec2f dimensions);
    Vec2f GetAbsolutePosition(WindowContext &ctx);

    void Button(const char *text);
    void Text(const char *text);
    void Canvas();
    void BeginBox(Axis axis, float percentage);
    void BeginBox(float percentage);
    void EndBox();
    void SetAxis(Axis axis);
}