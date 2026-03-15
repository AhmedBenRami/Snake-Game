#ifndef DECLS_HPP // to prevent from double inclusion
#define DECLS_HPP

#include <ctime>
#include <raylib.h>
#include <stdlib.h>
#include <inttypes.h>
#include <vector>

#include <iostream>

typedef struct
{
    int8_t x;
    int8_t y;
} Direction;

typedef struct
{
    Rectangle block;
    Color color;
    Direction dir;
} Node;

enum State
{
    STARTUP,
    PLAYING,
    PAUSED,
    GAMEOVER
};
typedef struct
{
    enum State state;
    Vector2 textPos;
    Color color;
} GameState;

#include "snake_class.hpp" // since snake class depends on those
#include "apple_class.hpp"

extern const unsigned short WIN_WIDTH;
extern const unsigned short WIN_HEIGHT;
extern const char *TITLE;

extern const uint8_t FPS;

extern const unsigned char blockSize;

extern GameState state;

extern Snake *snake;
extern Apple *apple;

extern bool isRunning;

extern Color bgColor;
extern Color fgColor;
extern Color gameoverFgColor;

// -- Functions section
void initialize();
void update();
void draw();
void close();
void showTitle();
void showManual();
void showMessage(char *msg, Color textColor);

#endif