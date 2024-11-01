#include "obstacle.h"
#include "game_data.h"
#include "raylib.h"

namespace spark_luchelli 
{

void initializeObstacle(Obstacle& obstacle) 
{
    obstacle.width = 30;
    obstacle.height = 250;
    obstacle.posX = SCREEN_WIDTH;
    obstacle.posY = static_cast<float>(GetRandomValue(0, SCREEN_HEIGHT - obstacle.height));
    obstacle.speed = 450.0f;
    obstacle.isActive = true;

}

void updateObstacle(Obstacle& obstacle) 
{
    if (obstacle.isActive)
    {
        obstacle.posX -= obstacle.speed * GetFrameTime();

        // If out of the screen, relocate
        if (obstacle.posX + obstacle.width < 0)
        {
            relocateObstacle(obstacle);
        }
    }
}

void drawObstacle(Obstacle obstacle) 
{
    DrawRectangle(static_cast<int>(obstacle.posX), static_cast<int>(obstacle.posY), static_cast<int>(obstacle.width), static_cast<int>(obstacle.height), RED);
}

void relocateObstacle(Obstacle& obstacle)
{
    obstacle.posX = SCREEN_WIDTH;
    obstacle.posY = static_cast<float>(GetRandomValue(0, SCREEN_HEIGHT - obstacle.height));
    obstacle.isActive = true;
}

} // namespace spark_luchelli