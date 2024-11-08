#include "scene_manager.h"
#include "state_machine.h"
#include "gameplay.h"
#include "main_menu.h"
#include "raylib.h"


namespace spark_luchelli
{

GameStateMachine gameState;
	
static void initialize();

static void update();

static void draw();

static void close();


void runProgram()
{
	initialize();

	while (!WindowShouldClose())
	{ 
		update();

		draw();
	}

	close();
}

static void initialize()
{
	InitWindow(800, 600, "BOKITA");

	initializeMenu(gameState);
	initializeGame(gameState);

	gameState.currentState = GAME_STATES::RUNNING;
	gameState.nextState = GAME_STATES::RUNNING;
}


static void update()
{
	switch (gameState.currentState)
	{
	case spark_luchelli::GAME_STATES::MENU:
		updateMenu(gameState);
		break;
	case spark_luchelli::GAME_STATES::PAUSED:
		break;
	case spark_luchelli::GAME_STATES::RUNNING:
		updateGame(gameState);
		break;
	case spark_luchelli::GAME_STATES::GAMEOVER:
		break;
	case spark_luchelli::GAME_STATES::CREDITS:
		break;
	default:
		break;
	}

	gameState.currentState = gameState.nextState;
}

static void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	switch (gameState.currentState)
	{
	case spark_luchelli::GAME_STATES::MENU:
		drawMenu();
		break;
	case spark_luchelli::GAME_STATES::PAUSED:
		break;
	case spark_luchelli::GAME_STATES::RUNNING:
		drawGame();
		break;
	case spark_luchelli::GAME_STATES::GAMEOVER:
		break;
	case spark_luchelli::GAME_STATES::CREDITS:
		break;
	default:
		break;
	}

	EndDrawing();
}

static void close()
{
	CloseWindow();
}

} // namespace spark_luchelli