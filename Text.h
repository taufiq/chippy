#ifndef TEXT_H
#define TEXT_H
#include "Node.h"
#include <string>
#include "Window.h"

namespace UI
{
    class Text : public Node
    {
    private:
        std::string value;

    public:
        void render(SDL_Renderer *renderer, TextManager *textManager, Context *ctx) override;
        Text(std::string _value);
        void measure(TextManager *textManager, int availableWidth, int availableHeight) override;
    };
}
#endif