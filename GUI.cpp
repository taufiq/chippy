#include "GUI.h"
#include <SDL3_ttf/SDL_ttf.h>
namespace GUI
{
    void InitAll(SDL_Renderer *renderer, TTF_TextEngine *textEngine)
    {
        WindowManager &mgr = GetManager();
        mgr.renderer = renderer;
        mgr.textEngine = textEngine;
        mgr.font = TTF_OpenFont("fonts/font.ttf", 20);
        mgr.stack = new WindowContext[CONTEXT_STACK_SIZE];
    }

    void Start(int width, int height)
    {
        WindowManager &mgr = GetManager();
        WindowContext &ctx = GetContext();

        ctx.size.x = static_cast<float>(width);
        ctx.size.y = static_cast<float>(height);

        ctx.cursor.x = 0;
        ctx.cursor.y = 0;

        ctx.position.x = 0;
        ctx.position.y = 0;
    }

    void End()
    {
        WindowManager &mgr = GetManager();
        mgr.stackIndex = 0;
        memset(mgr.stack, 0, CONTEXT_STACK_SIZE * sizeof(*mgr.stack));
    }

    WindowManager &GetManager()
    {
        static WindowManager mgr{};
        return mgr;
    }
    WindowContext &GetContext()
    {
        WindowManager &mgr = GetManager();
        return mgr.stack[mgr.stackIndex];
    }

    void PushContext()
    {
        WindowManager &mgr = GetManager();
        mgr.stackIndex++;
        mgr.stack[mgr.stackIndex].position = mgr.stack[mgr.stackIndex - 1].position;
        mgr.stack[mgr.stackIndex].position.x += mgr.stack[mgr.stackIndex - 1].cursor.x;
        mgr.stack[mgr.stackIndex].position.y += mgr.stack[mgr.stackIndex - 1].cursor.y;

        mgr.stack[mgr.stackIndex].cursor = Vec2f{};
        mgr.stack[mgr.stackIndex].size = Vec2f{};
        mgr.stack[mgr.stackIndex].axis = Axis::Horizontal;
    }

    void PopContext()
    {
        WindowManager &mgr = GetManager();
        if (mgr.stackIndex == 0)
        {
            return;
        }
        mgr.stackIndex--;
    }

    Vec2f GetAbsoluteCursorPosition(WindowContext &ctx)
    {
        return (Vec2f){
            .x = ctx.position.x + ctx.cursor.x,
            .y = ctx.position.y + ctx.cursor.y,
        };
    }

    void Button(const char *text)
    {
        int w, h;
        WindowManager &mgr = GetManager();
        WindowContext &parentCtx = GetContext();

        Vec2f cursorPosition = GetAbsoluteCursorPosition(parentCtx);

        TTF_GetStringSizeWrapped(mgr.font, text, 0, 0, &w, &h);

        SDL_FRect rectangle{cursorPosition.x, cursorPosition.y, static_cast<float>(w), static_cast<float>(h)};

        SDL_SetRenderDrawColor(mgr.renderer, 255, 0, 255, 255);
        SDL_RenderRect(mgr.renderer, &rectangle);
        TTF_DrawRendererText(TTF_CreateText(mgr.textEngine, mgr.font, text, 0), rectangle.x, rectangle.y);

        AdvanceCursor((Vec2f){.x = static_cast<float>(w), .y = static_cast<float>(h)});
    }

    void AdvanceCursor(Vec2f dimensions)
    {
        WindowContext &ctx = GetContext();
        SDL_Log("X: %f, Y: %f", dimensions.x, dimensions.y);
        if (ctx.axis == Axis::Horizontal)
        {
            ctx.cursor.x += dimensions.x;
        }
        else
        {
            ctx.cursor.y += dimensions.y;
        }
    }

    void Text(const char *text);
    void Canvas();
    void BeginBox(Axis axis, float percentage)
    {
        WindowContext &parentCtx = GetContext();
        PushContext();
        SetAxis(axis);
        WindowContext &childCtx = GetContext();

        if (parentCtx.axis == Axis::Horizontal)
        {
            childCtx.size.x = parentCtx.size.w() * percentage;
            childCtx.size.y = parentCtx.size.y;
        }
        else
        {
            childCtx.size.x = parentCtx.size.x;
            childCtx.size.y = parentCtx.size.h() * percentage;
        }
    }

    void BeginBox(float percentage) { BeginBox(Axis::Horizontal, percentage); };

    // TODO: Figure out how to clip shit
    void EndBox()
    {
        WindowManager &mgr = GetManager();
        WindowContext &childCtx = GetContext();
        PopContext();
        WindowContext &parentCtx = GetContext();

        float widthDiff = parentCtx.size.x - childCtx.size.x;
        float heightDiff = parentCtx.size.y - childCtx.size.y;
        SDL_FRect rect{
            childCtx.position.x + childCtx.size.x,
            0,
            parentCtx.position.x + parentCtx.size.x - childCtx.position.x - childCtx.size.x,
            parentCtx.position.y + parentCtx.size.y - childCtx.position.y - childCtx.size.y,
        };
        if (widthDiff == 0)
        {
            rect.w = parentCtx.size.w();
        }
        else
        {
            rect.h = parentCtx.size.h();
        }
        SDL_SetRenderDrawColor(mgr.renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(mgr.renderer, &rect);

        AdvanceCursor(childCtx.size);
    }

    void SetAxis(Axis axis)
    {
        WindowContext &ctx = GetContext();
        ctx.axis = axis;
    }
}
/**
 * GUI::Start();
 * GUI::Text("Hello");
 * GUI::BeginBox();
 *  GUI::Text("Alice");
 *  GUI::Text("Bob");
 * GUI::End();
 */