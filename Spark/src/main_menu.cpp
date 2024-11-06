#include "main_menu.h"
#include "state_machine.h"

namespace spark_luchelli
{

void initializeMenu()
{
	
}

void drawMenu()
{

}

void updateMenu()
{

}

void initializeButtons(Button& play, Button& credits, Button& exit)
{
	play = createButton({ 100, 100 }, { 150, 50 }, "Play");
	credits = createButton({ 100, 300 }, { 150, 50 }, "Credits");
	exit = createButton({ 100, 500 }, { 150, 50 }, "Exit");
}

} // namespace spark_luchelli

