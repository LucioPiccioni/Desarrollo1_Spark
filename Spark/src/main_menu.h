#include "button.h"
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

namespace spark_luchelli
{

Button playButton;
Button creditsButton;
Button exitButton;

void initializeMenu();

void drawMenu();

void updateMenu();

void initializeButtons(Button& play, Button& credits, Button& exit);


} // spark_luchelli
#endif // MAIN_MENU_H