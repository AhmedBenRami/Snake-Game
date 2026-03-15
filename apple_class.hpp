#ifndef APPLE_HPP
#define APPLE_HPP

#include "decls.hpp"

class Apple
{
    Rectangle block;
    Color color;

    // range of respawning of the apple
    float maxX, maxY;

    Sound ping;

public:
    unsigned int score;

    Apple();

    void initAudio();

    void update();

    void draw();

    ~Apple();
};

#endif