#include "scene_manager.h"
#include "state_machine.h"
#include "gameplay.h"
#include "main_menu.h"
#include "raylib.h"


namespace SCENE_MANAGER
{

	GAME_STATES::GAME_STATES gameState;

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

		MAIN_MENU::initializeMenu(gameState);
		GamePlay::initializeGame(gameState);

		gameState.currentState = GAME_STATES::GAME_STATES::RUNNING;
		gameState.nextState = GAME_STATES::GAME_STATES::RUNNING;
	}


	static void update()
	{
		switch (gameState.currentState)
		{
		case GAME_STATES::GAME_STATES::MENU:
			MAIN_MENU::updateMenu(gameState);
			break;
		case GAME_STATES::GAME_STATES::PAUSED:
			break;
		case GAME_STATES::GAME_STATES::RUNNING:
			GamePlay::updateGame(gameState);
			break;
		case GAME_STATES::GAME_STATES::GAMEOVER:
			break;
		case GAME_STATES::GAME_STATES::CREDITS:
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
		case Obstacle::GAME_STATES::MENU:
			drawMenu();
			break;
		case Obstacle::GAME_STATES::PAUSED:
			break;
		case Obstacle::GAME_STATES::RUNNING:
			drawGame();
			break;
		case Obstacle::GAME_STATES::GAMEOVER:
			break;
		case Obstacle::GAME_STATES::CREDITS:
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