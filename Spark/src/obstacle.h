#ifndef OBSTACLE_H
#define OBSTACLE_H

namespace spark_luchelli 
{

    struct Obstacle 
    {
        float posX;
        float posY;
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