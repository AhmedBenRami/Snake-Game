#include "decls.hpp"

void initialize()
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, TITLE);
    SetTargetFPS(FPS);

    if (!IsWindowReady())
    {
        exit(1);
    }
    snake->initHead();

    InitAudioDevice();
    if (!IsAudioDeviceReady())
    {
        exit(2);
    }

    apple->initAudio();
    // init game state to be playing
    state.state = PAUSED;
    state.textPos = Vector2{10, 10};
    state.color = WHITE;
}

void update()
{
    switch (state.state)
    {
    case PLAYING:
        state.color = WHITE;
        snake->getKey();
        snake->update();
        snake->checkWallCollision();
        snake->checkCollision();

        apple->update();

        // to change from play to pause
        if (IsKeyPressed(KEY_SPACE))
        {
            state.state = PAUSED;
        }
        break;

    case PAUSED:
        state.color = GREEN;
        if (IsKeyPressed(KEY_SPACE))
        {
            state.state = PLAYING;
        }
        break;

    case GAMEOVER:
        state.color = RED;
        if (IsKeyPressed(KEY_SPACE))
        {
            isRunning = false;
        }
        break;
    }
}

void draw()
{

    BeginDrawing();

    ClearBackground(BLACK);

    snake->draw();

    apple->draw();

    DrawText(
        ((state.state == PLAYING) ? "PLAYING" : (state.state == PAUSED) ? "PAUSED"
                                                                        : "GAMEOVER"),
        state.textPos.x, state.textPos.y, 15, state.color);

    DrawText(TextFormat("SCORE : %d", apple->score), 10, 25, 15, WHITE);

    EndDrawing();
}

void close()
{
    delete snake;
    delete apple;
    CloseWindow();
}
