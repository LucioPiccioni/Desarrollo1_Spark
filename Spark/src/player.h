#ifndef PLAYER_H
#define PLAYER_H

namespace spark_luchelli
{

struct Player 
{
    float posX;
    float posY;
    int gravityValue;
    int height;
    int width;
    int speed;
};

void initializePlayer(Player& player);

void resetPlayer(Player& player);

void movePlayerUp(Player& player);

void movePlayerDown(Player& player);

void drawPlayer(Player& player);


} // namespace spark_luchelli

#endif // PLAYER_H