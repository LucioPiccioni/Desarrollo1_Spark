#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "state_machine.h"


namespace spark_luchelli
{

void initializeMenu(GameStateMachine& gameState);

void updateMenu(GameStateMachine& gameState);

void drawMenu();


} // spark_luchelli

#endif // MAIN_MENU_H