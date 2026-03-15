#include "decls.hpp"

Snake::Snake()
{
    fpsTiming = 30;
    fpsCounter = 0;

    // init the head
    Node temp;
    temp.block.width = blockSize;
    temp.block.height = blockSize;
    temp.dir = {1, 0};
    temp.block.x = WIN_WIDTH / 2 - temp.block.width * temp.dir.x;
    temp.block.y = WIN_HEIGHT / 2 - temp.block.height * temp.dir.y;
    temp.color = Color{(unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), 255};

    listBlocks.push_back(temp);
}

void Snake::initHead()
{

    head = LoadTexture("head.png");

    if (!IsTextureValid(head))
    {
        exit(4);
    }

    headRotation = 0;
    headPosition = {listBlocks[0].block.x, listBlocks[0].block.y};
}

void Snake::getKey()
{
    if (IsKeyPressed(KEY_LEFT) && listBlocks[0].dir.x == 0)
    {
        listBlocks[0].dir.x = -1;
        listBlocks[0].dir.y = 0;
    }
    else if (IsKeyPressed(KEY_RIGHT) && listBlocks[0].dir.x == 0)
    {
        listBlocks[0].dir.x = 1;
        listBlocks[0].dir.y = 0;
    }

    if (IsKeyPressed(KEY_UP) && listBlocks[0].dir.y == 0)
    {
        listBlocks[0].dir.y = -1;
        listBlocks[0].dir.x = 0;
    }
    else if (IsKeyPressed(KEY_DOWN) && listBlocks[0].dir.y == 0)
    {
        listBlocks[0].dir.y = 1;
        listBlocks[0].dir.x = 0;
    }
}

void Snake::update()
{
    if (fpsCounter < fpsTiming)
    {
        fpsCounter++;
        return;
    }
    fpsCounter = 0;

    // Move the body: Each block takes the position of the one in front of it
    for (int i = listBlocks.size() - 1; i > 0; i--)
    {
        listBlocks[i].block.x = listBlocks[i - 1].block.x;
        listBlocks[i].block.y = listBlocks[i - 1].block.y;
    }

    // Move the head based on its current direction
    listBlocks[0].block.x += listBlocks[0].dir.x * listBlocks[0].block.width;
    listBlocks[0].block.y += listBlocks[0].dir.y * listBlocks[0].block.height;

    // give the head texture the first block position
    headPosition = Vector2{listBlocks[0].block.x, listBlocks[0].block.y};
    // change the head rotation
    if (listBlocks[0].dir.x == 1)
    {
        headRotation = 0;
    }
    else if (listBlocks[0].dir.x == -1)
    {
        headRotation = 180;
        headPosition.x += listBlocks[0].block.width;
        headPosition.y += listBlocks[0].block.height;
    }
    else if (listBlocks[0].dir.y == -1)
    {
        headRotation = 270;
        headPosition.y += listBlocks[0].block.height;
    }
    else if (listBlocks[0].dir.y == 1)
    {
        headRotation = 90;
        headPosition.x += listBlocks[0].block.width;
    }
}

void Snake::checkCollision()
{
    if (listBlocks.size() <= 3)
    {
        return; // no collision is possible
    }

    for (int i = 1; i < listBlocks.size(); i++)
    {
        if (CheckCollisionRecs(listBlocks[0].block, listBlocks[i].block))
        {
            state.state = GAMEOVER;
            break;
        }
    }
}

void Snake::checkWallCollision()
{
    if (listBlocks[0].block.x < 0 ||
        listBlocks[0].block.x >= WIN_WIDTH ||
        listBlocks[0].block.y < 0 ||
        listBlocks[0].block.y >= WIN_HEIGHT)
    {
        state.state = GAMEOVER;
    }
}

void Snake::draw()
{
    for (auto block : listBlocks)
    {
        DrawRectangleRec(block.block, block.color);
    }

    // DrawTexture(head, listBlocks[0].block.x, listBlocks[0].block.y, WHITE);
    DrawTextureEx(head, headPosition, headRotation, 1, WHITE);
}

void Snake::addNode()
{
    Node prev = listBlocks.back();

    Node temp;

    temp.block = prev.block;
    temp.dir = prev.dir;

    temp.block.x -= temp.block.width * temp.dir.x;
    temp.block.y -= temp.block.height * temp.dir.y;

    temp.color = Color{(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255};
    // temp.color = GREEN;

    listBlocks.push_back(temp);
}