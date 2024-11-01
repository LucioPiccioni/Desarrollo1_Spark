#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace spark_luchelli
{

struct Player 
{
    float posX;
    float posY;
    int speed;
    int height;
    int width;
};

void initializePlayer(Player& player);

void resetPlayer(Player& player);

void movePlayerUp(Player& player);

void movePlayerDown(Player& player);

void drawPlayer(Player& player);


} // namespace spark_luchelli

#endif // PLAYER_H