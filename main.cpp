#include <iostream>
#include <iterator>
#include <fstream>
#include <SDL.h>
#include <cstdlib>
#include <string_view>
#include "constants.h"
#include "Window.h"

int main()
{
    Window window{};
    window.initialize();
    window.run();
    window.cleanup();
    return 0;
}