#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "decls.hpp"

class Snake
{
public:
    // update every 30 frame
    uint8_t fpsCounter;
    uint8_t fpsTiming;

    std::vector<Node> listBlocks;

    Texture2D head;
    float headRotation;
    Vector2 headPosition;

    Snake();

    void initHead();
    void getKey();

    void update();

    void checkCollision();

    void draw();

    void checkWallCollision();

    void addNode();
};

// inline Snake snake;

#endif