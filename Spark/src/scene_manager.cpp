#include "scene_manager.h"

#include "raylib.h"

#include "state_machine.h"

#include "gameplay.h"

#include "pause.h"

#include "game_over.h"

#include "main_menu.h"
#include "sprites.h"
#include "player.h"

namespace SCENE_MANAGER
{
	GAME_STATES::GAME_STATES gameState = GAME_STATES::GAME_STATES::MAIN_MENU;


	void runProgram()
	{
		initialize();

		while (!WindowShouldClose() && gameState != GAME_STATES::GAME_STATES::EXIT)
		{
			update();

			draw();
		}

		close();
	}

	void initialize()
	{
		InitWindow(800, 600, "Flappy Bird");

		Sprites::initSprites(GAMEPLAY::sprites);
		GAMEPLAY::initializeGame();
		MAIN_MENU::initializeMenu();
		PAUSE::initButtons();
		GAME_OVER::initButtons();

		SetExitKey(0);
	}

	void update()
	{
		switch (gameState)
		{
		case GAME_STATES::GAME_STATES::MAIN_MENU:
			MAIN_MENU::updateMenu(gameState);
			break;

		case GAME_STATES::GAME_STATES::PLAYING:
			GAMEPLAY::updateGame(gameState);
			break;

		case GAME_STATES::GAME_STATES::PAUSE:
			PAUSE::update(gameState);
			break;

		case GAME_STATES::GAME_STATES::GAME_OVER:
			GAME_OVER::update(gameState);
			break;

		case GAME_STATES::GAME_STATES::RULES:
			break;

		case GAME_STATES::GAME_STATES::CREDITS:
			break;

		case GAME_STATES::GAME_STATES::WANT_TO_EXIT:
			break;

		default:
			break;
		}
	}

	void draw()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case GAME_STATES::GAME_STATES::MAIN_MENU:
			MAIN_MENU::drawMenu();
			break;

		case GAME_STATES::GAME_STATES::PLAYING:
			GAMEPLAY::drawGame();
			break;

		case GAME_STATES::GAME_STATES::PAUSE:
			PAUSE::draw(GetFontDefault());
			break;

		case GAME_STATES::GAME_STATES::GAME_OVER:
			GAME_OVER::draw(GetFontDefault());
			break;

		case GAME_STATES::GAME_STATES::RULES:
			break;

		case GAME_STATES::GAME_STATES::CREDITS:
			break;

		case GAME_STATES::GAME_STATES::WANT_TO_EXIT:
			break;

		default:
			break;
		}


		EndDrawing();
	}

	void close()
	{
		GAMEPLAY::unInitGame();
		CloseWindow();
	}

}