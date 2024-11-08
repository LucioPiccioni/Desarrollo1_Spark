#include "gameplay.h"
#include "scene_manager.h"
#include "state_machine.h"
#include "game_data.h"
#include "player.h"
#include "obstacle.h"
#include "raylib.h"


namespace spark_luchelli
{

static Player player;
static Obstacle obstacle;

static void updatePlayer();
static void checkCollisionRectRect();


void initializeGame(GameStateMachine& gameState)
{
    initializePlayer(player);
    initializeObstacle(obstacle);
}

void updateGame(GameStateMachine& gameState)
{
    updatePlayer();
    updateObstacle(obstacle);
    checkCollisionRectRect();
}

void drawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Spark v0.1", 10, 10, 20, LIGHTGRAY);
    drawPlayer(player);
    drawObstacle(obstacle);

    EndDrawing();
}

void closeGame()
{
    gameState.nextState = GAME_STATES::MENU;
}

static void updatePlayer()
{
    movePlayerDown(player);

    if (IsKeyPressed(KEY_UP))
    {
        movePlayerUp(player);
    }
}

static void checkCollisionRectRect()
{
    if (obstacle.isActive)
    {
        // This condition checks if the player and obstacle rectangles overlap
        bool collision =
            // Check if the player's left edge is to the left of the obstacle's right edge
            player.posX < obstacle.pos1.x + obstacle.width &&
            // Check if the player's right edge is to the right of the obstacle's left edge
            player.posX + player.width > obstacle.pos1.x &&
            // Check if the player's top edge is above the obstacle's bottom edge
            player.posY < obstacle.pos1.y + obstacle.height &&
            // Check if the player's bottom edge is below the obstacle's top edge
            player.posY + player.height > obstacle.pos1.y;

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