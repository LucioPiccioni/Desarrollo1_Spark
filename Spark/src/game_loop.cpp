#include "game_loop.h"
#include "game_data.h"
#include "player.h"
#include "raylib.h"

namespace spark_luchelli
{

Player player;
GameStateMachine gameState;

void updatePlayer(Player& auxPlayer);

void runGame()
{
    initializeGame();

    while (!WindowShouldClose()) 
    {
        update();

        draw();
    }

    close();
}

void initializeGame()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Spark v0.1");
    SetTargetFPS(60);
    initializePlayer(player);

    gameState.currentState = GAME_STATES::RUNNING;
    gameState.nextState = GAME_STATES::RUNNING;
}

void update()
{
    switch (gameState.currentState)
    {
    case GAME_STATES::PAUSED:
        
        break;
    case GAME_STATES::RUNNING:
        updatePlayer(player);
        break;
    case GAME_STATES::GAMEOVER:

        break;
    case GAME_STATES::CREDITS:

        break;
    default:
        break;
    }

    gameState.currentState = gameState.nextState;
}

void draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (gameState.currentState)
    {
    case spark_luchelli::GAME_STATES::NOT_STARTED:
        break;
    case spark_luchelli::GAME_STATES::PAUSED:
        break;
    case spark_luchelli::GAME_STATES::RUNNING:
        drawPlayer(player);
        DrawText("Spark v0.1", 10, 10, 20, LIGHTGRAY);
        break;
    case spark_luchelli::GAME_STATES::GAMEOVER:
        break;
    case spark_luchelli::GAME_STATES::CREDITS:
        break;
    default:
        break;
    }

    EndDrawing();
}

void close()
{
    CloseWindow();
}

void updatePlayer(Player& auxPlayer)
{
    if (IsKeyDown(KEY_UP))
    {
        movePlayerUp(auxPlayer);
    }
    if (IsKeyDown(KEY_DOWN))
    {
        movePlayerDown(auxPlayer);
    }
}


} //namespace spark_luchelli