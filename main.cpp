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
