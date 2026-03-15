#include "decls.hpp"

const unsigned short WIN_WIDTH = 600;
const unsigned short WIN_HEIGHT = 600;
const char *TITLE = "title";

const unsigned char FPS = 60;

const unsigned char blockSize = 30;

Snake *snake = new Snake();
Apple *apple = new Apple();

GameState state;

bool isRunning = true;

// definning colors
Color bgColor = {0x12, 0x12, 0x12, 0xff};
Color fgColor = {0xF8, 0xF9, 0xFA, 0xff};
Color gameoverFgColor = {0xFF, 0x5F, 0x5F, 0xff};

int main()
{

    initialize();

    while (!WindowShouldClose() && isRunning)
    {
        update();
        draw();
    }
    close();
}
