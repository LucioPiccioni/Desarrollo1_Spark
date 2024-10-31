#include "game_loop.h"
#include "raylib.h"

namespace spark_luchelli
{


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

}

void update()
{

}

void draw()
{

}

void close()
{

}



} //namespace spark_luchelli