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
    state.state = STARTUP;
    state.textPos = Vector2{10, 10};
    state.color = fgColor;
}

void update()
{
    switch (state.state)
    {
    case STARTUP:
        // state.state = PAUSED;
        break;

    case PLAYING:
        state.color = fgColor;
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
        if (IsKeyPressed(KEY_SPACE))
        {
            state.state = PLAYING;
        }
        break;

    case GAMEOVER:
        state.color = gameoverFgColor;
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

    ClearBackground(bgColor);

    snake->draw();

    apple->draw();

    DrawText(TextFormat("SCORE : %d", apple->score), 10, 10, 15, fgColor);

    // to show the states
    if (state.state != PLAYING)
    {
        // to show manual at the beginning
        if (state.state == STARTUP)
        {
            showTitle();
            showManual();
        }
        else
            showMessage((state.state == PAUSED) ? (char *)"PAUSED" : (char *)"GAMEOVER", state.color);
    }

    EndDrawing();
}

void close()
{
    delete apple;
    delete snake;
    CloseWindow();
}

void showTitle()
{
    // draw the bg
    static Rectangle box = {0, 0, (float)WIN_WIDTH, (float)WIN_HEIGHT};
    DrawRectangleRec(box, bgColor);

    // define bg of title
    static Rectangle border;
    static Color borderColor = fgColor;
    // define title
    static unsigned short counter = 1;
    static Color titleColor = bgColor;
    static char title[] = "SNAKE";
    static float fontSize = 100;

    static Vector2 titleMeasure = {-1, -1};
    if (titleMeasure.x == -1 && titleMeasure.y == -1)
    {
        titleMeasure = MeasureTextEx(GetFontDefault(), title, fontSize, 10);
        border.width = titleMeasure.x;
        border.height = titleMeasure.y;

        titleMeasure.x = (WIN_WIDTH - titleMeasure.x) / 2;
        titleMeasure.y = (WIN_HEIGHT - titleMeasure.y) / 2 - 100;
        border.x = titleMeasure.x;
        border.y = titleMeasure.y;
    }

    if (counter % FPS == 0)
    {
        Color temp = borderColor;
        borderColor = titleColor;
        titleColor = temp;
    }

    DrawRectangleRec(border, borderColor);
    DrawText(title, titleMeasure.x, titleMeasure.y, fontSize, titleColor);

    counter++;
}

void showManual()
{

    static char control[] = "CONTROL : ARROWS";
    static float controlFontSize = 20;

    static char startMsg[] = "Press SPACE to start the game";
    static float startFontSize = 13;

    // control
    static Vector2 controlMeasure = {-1, -1};
    if (controlMeasure.x == -1 && controlMeasure.y == -1)
    {
        controlMeasure = MeasureTextEx(GetFontDefault(), startMsg, startFontSize, 1.5);
        controlMeasure.x = (WIN_WIDTH - controlMeasure.x) / 2;
        controlMeasure.y = (WIN_HEIGHT - controlMeasure.y) / 2 + 100;
    }
    DrawText(control, controlMeasure.x, controlMeasure.y, controlFontSize, fgColor);

    // start request
    static Vector2 startMeasure = {-1, -1};
    if (startMeasure.x == -1 && startMeasure.y == -1)
    {
        startMeasure = MeasureTextEx(GetFontDefault(), startMsg, startFontSize, 1.5);
        startMeasure.x = (WIN_WIDTH - startMeasure.x) / 2;
        startMeasure.y = (WIN_HEIGHT - startMeasure.y) / 2 + 200;
    }
    DrawText(startMsg, startMeasure.x, startMeasure.y, startFontSize, fgColor);

    if (IsKeyPressed(KEY_SPACE))
    {
        state.state = PLAYING;
    }
}

void showMessage(char *msg, Color textColor)
{
    static Rectangle box = {0, 0, (float)WIN_WIDTH, (float)WIN_HEIGHT};
    static Color boxColor = {0, 0, 0, 127};
    static float fontSize = 25;
    static Vector2 textMeasures = {-1, -1};

    if (textMeasures.x == -1 && textMeasures.y == -1)
    {
        textMeasures = MeasureTextEx(GetFontDefault(), msg, fontSize, 0);
        textMeasures.x = (WIN_WIDTH - textMeasures.x) / 2;
        textMeasures.y = (WIN_HEIGHT - textMeasures.y) / 2;
    }

    DrawRectangleRec(box, boxColor);

    DrawText(msg, textMeasures.x, textMeasures.y, fontSize, textColor);
}