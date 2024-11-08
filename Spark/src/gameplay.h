#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "state_machine.h"

namespace spark_luchelli
{

void initializeGame(GameStateMachine& gameState);

void updateGame(GameStateMachine& gameState);

void drawGame();

void closeGame();

} //namespace spark_luchelli

#endif //GAMEPLAY_H