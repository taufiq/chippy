#ifndef TEXT_H
#define TEXT_H
#include "Node.h"
#include <string>
#include <functional>
#include "MainWindow.h"

namespace UI
{
    class Text : public Node
    {
    private:
        std::function<std::string()> value{[]()
                                           { return ""; }};
        Bounds minimumBoundsForText{};

    public:
        void onMouseMove(float x, float y) override;
        void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) override;
        Text(std::function<std::string()> value);
        void measure(TextManager *textManager, float availableWidth, float availableHeight) override;
        void setBounds(Bounds _bounds) override;
    };
}
#endif