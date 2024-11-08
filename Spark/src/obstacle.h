#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

namespace spark_luchelli 
{

    struct Obstacle 
    {
        Vector2 pos1;
        Vector2 pos2;
        float speed;
        int width;
        int height;
        bool isActive;
    };

    void initializeObstacle(Obstacle& obstacle);

    void updateObstacle(Obstacle& obstacle);

    void drawObstacle(Obstacle obstacle);

    void relocateObstacle(Obstacle& obstacle);

} // namespace spark_luchelli

#endif // OBSTACLE_H