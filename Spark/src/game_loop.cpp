#include "game_loop.h"
#include "state_machine.h"
#include "game_data.h"
#include "player.h"
#include "obstacle.h"
#include "raylib.h"

namespace spark_luchelli
{

Player player;
Obstacle obstacle;
GameStateMachine gameState;

static void updatePlayer(Player& auxPlayer);
static void checkCollisionRectRect();

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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Spark");
    SetTargetFPS(60);
    initializePlayer(player);
    initializeObstacle(obstacle);

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
        updateObstacle(obstacle);
        checkCollisionRectRect();
        break;
    case GAME_STATES::GAMEOVER:
        if (IsKeyReleased(KEY_BACKSPACE))
        {
            gameState.nextState = GAME_STATES::RUNNING;
        }
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
        DrawText("Spark v0.1", 10, 10, 20, LIGHTGRAY);
        drawPlayer(player);
        drawObstacle(obstacle);
        break;
    case spark_luchelli::GAME_STATES::GAMEOVER:
        DrawText("Game Over", (GetScreenWidth() / 2) - (MeasureText("Game Over", 60) / 2), GetScreenHeight() / 2, 60, RAYWHITE);
        DrawText("Press [BACKSPACE] to Restart", (GetScreenWidth() / 2) - (MeasureText("Press [BACKSPACE] to Restart", 20) / 2), (GetScreenHeight() / 4) * 3, 20, LIGHTGRAY);
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
    movePlayerDown(auxPlayer);

    if (IsKeyPressed(KEY_UP))
    {
        movePlayerUp(auxPlayer);
    }
}

void checkCollisionRectRect() 
{
    if (obstacle.isActive)
    {
        // This condition checks if the player and obstacle rectangles overlap
        bool collision =
            // Check if the player's left edge is to the left of the obstacle's right edge
            player.posX < obstacle.posX + obstacle.width &&
            // Check if the player's right edge is to the right of the obstacle's left edge
            player.posX + player.width > obstacle.posX &&
            // Check if the player's top edge is above the obstacle's bottom edge
            player.posY < obstacle.posY + obstacle.height &&
            // Check if the player's bottom edge is below the obstacle's top edge
            player.posY + player.height > obstacle.posY;

        //TODO: Remove this check from here
        if (collision)
        {
            gameState.nextState = GAME_STATES::GAMEOVER;
            obstacle.isActive = false;
            relocateObstacle(obstacle);
        }
    }
}

} //namespace spark_luchelli