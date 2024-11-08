#include "obstacle.h"
#include "game_data.h"

#include "raylib.h"

namespace spark_luchelli 
{

void initializeObstacle(Obstacle& obs) 
{
    obs.width = 30;
    obs.height = 250;
    obs.pos1.x = SCREEN_WIDTH;
    obs.pos1.y = static_cast<float>(GetRandomValue(0, (SCREEN_HEIGHT / 2) - obs.height));
    obs.pos1.x = SCREEN_WIDTH;
    obs.pos1.y = static_cast<float>(GetRandomValue((SCREEN_HEIGHT / 2), SCREEN_HEIGHT - obs.height));
    obs.speed = 450.0f;
    obs.isActive = true;

}

void updateObstacle(Obstacle& obstacle) 
{
    if (obstacle.isActive)
    {
        obstacle.pos1.x -= obstacle.speed * GetFrameTime();

        // If out of the screen, relocate
        if (obstacle.pos1.x + obstacle.width < 0)
        {
            relocateObstacle(obstacle);
        }
    }
}

void drawObstacle(Obstacle obstacle)
{
    DrawRectangle(static_cast<int>(obstacle.pos1.x), static_cast<int>(obstacle.pos1.y), static_cast<int>(obstacle.width), static_cast<int>(obstacle.height), RED);
}

void relocateObstacle(Obstacle& obstacle)
{
    obstacle.pos1.x = SCREEN_WIDTH;
    obstacle.pos1.y = static_cast<float>(GetRandomValue(0, SCREEN_HEIGHT - obstacle.height));
    obstacle.isActive = true;
}

} // namespace spark_luchelli