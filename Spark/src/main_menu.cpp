#include "main_menu.h"
#include "button.h"

namespace spark_luchelli
{


static Button playButton;
static Button creditsButton;
static Button exitButton;

static void initializeButtons();


void initializeMenu(spark_luchelli::GameStateMachine& gameState)
{
	initializeButtons();
	gameState.currentState = GAME_STATES::MENU;
	gameState.nextState = GAME_STATES::MENU;
}

void updateMenu(spark_luchelli::GameStateMachine& gameState)
{
	if (isButtonClicked(playButton))
	{
		gameState.nextState = GAME_STATES::RUNNING;
	}
}

void drawMenu()
{
	// Draw Title
	
	drawButton(playButton);
	drawButton(creditsButton);
	drawButton(exitButton);
}

static void initializeButtons()
{
	playButton = createButton({ 100, 100 }, { 150, 50 }, "Play");
	creditsButton = createButton({ 100, 300 }, { 150, 50 }, "Credits");
	exitButton = createButton({ 100, 500 }, { 150, 50 }, "Exit");
}

} // namespace spark_luchelli

