#include <iostream>
#include <iterator>
#include <fstream>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <string_view>
#include "constants.h"
#include "Window.h"

TextManager gTextManager{};
Window gWindow{&gTextManager};

int main()
{
    gWindow.initialize();
    gWindow.run();
    gWindow.cleanup();
    return 0;
}