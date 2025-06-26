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
        bool scrollable{false};
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

        SDL_Renderer *renderer{nullptr};
        TTF_TextEngine *textEngine{nullptr};
        TTF_Font *font{nullptr};

        [[maybe_unused]] std::vector<UIButton> buttons;
        [[maybe_unused]] std::vector<UIText> texts;

        Vec2f mousePosition{};
        Vec2f scrollDelta{};
        Vec2f *offsets{nullptr};
        uint activeId{0};
    } WindowManager;

    void InitAll(SDL_Renderer *renderer, TTF_TextEngine *textEngine);

    void Start(int width, int height);
    void End();

    WindowManager &GetManager();
    WindowContext &GetContext();

    void PushContext();
    void PopContext();
    void AdvanceCursor(Vec2f dimensions);
    void SetMousePosition(Vec2f coordinates);
    void SetScrollDelta(Vec2f delta);

    uint &GenId();
    uint &ResetId();

    Vec2f GetAbsolutePosition(WindowContext &ctx);
    Vec4f GetAvailableSpace(WindowContext &parentCtx, WindowContext &childCtx);
    SDL_FRect Vec4fToFRect(Vec4f vec);
    bool IsInBounds(Vec2f position, Vec2f size, Vec2f cursor);

    void Button(const char *text);
    void Text(const char *text);
    void Canvas();
    void BeginBox(Axis axis, float percentage);
    void BeginBox(float percentage);
    void EndBox();
    void SetAxis(Axis axis);
    void MakeScrollable();
}