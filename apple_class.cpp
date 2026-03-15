#include "decls.hpp"

Apple::Apple()
{
    block.width = blockSize;
    block.height = block.width;
    maxX = WIN_WIDTH - block.width;
    maxY = WIN_HEIGHT - block.height;
    block.x = GetRandomValue(0, maxX);
    block.y = GetRandomValue(0, maxY);

    color = RED;
    score = 0;
}

void Apple::initAudio()
{
    ping = LoadSound("./nothing.wav");

    if (!IsSoundValid(ping))
    {
        exit(3);
    };
}

void Apple::update()
{
    if (CheckCollisionRecs(snake->listBlocks[0].block, this->block))
    {
        PlaySound(ping);

        SetRandomSeed(time(NULL));

        // to ensure the apple doesnt get on the snake's body
        bool isFull;
        do
        {
            isFull = false;
            block.x = GetRandomValue(0, maxX);
            block.y = GetRandomValue(0, maxY);

            for (auto snakeBlock : snake->listBlocks)
            {
                if (CheckCollisionRecs(block, snakeBlock.block))
                {
                    isFull = true;
                    break;
                }
            }

        } while (isFull);

        block.x -= (int)block.x % (int)block.width;
        block.y -= (int)block.y % (int)block.height;

        snake->addNode();
        snake->fpsTiming = (snake->fpsTiming <= 1) ? 1 : snake->fpsTiming - 1;
        score++;
    }
}

void Apple::draw()
{
    DrawRectangleRec(block, color);
}

Apple::~Apple()
{
    UnloadSound(ping);
}