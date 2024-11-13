#include "scene_manager.h"

#include "raylib.h"

#include "state_machine.h"

#include "gameplay.h"
#include "gameplay2p.h"

#include "pause.h"

#include "game_over.h"

#include "main_menu.h"
#include "sprites.h"
#include "player.h"

namespace SCENE_MANAGER
{
	GAME_STATES::GAME_STATES gameState = GAME_STATES::GAME_STATES::MAIN_MENU;
	GAME_STATES::GAME_STATES previusGameMode = GAME_STATES::GAME_STATES::NONE;

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

		Sprites::initSprites();
		GAMEPLAY1P::initializeGame();
		GAMEPLAY2P::initializeGame();
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

		case GAME_STATES::GAME_STATES::ONE_PLAYER_MODE:
			previusGameMode = GAME_STATES::GAME_STATES::ONE_PLAYER_MODE;
			GAMEPLAY1P::updateGame(gameState);
			break;

		case GAME_STATES::GAME_STATES::TWO_PLAYER_MODE:
			previusGameMode = GAME_STATES::GAME_STATES::TWO_PLAYER_MODE;
			GAMEPLAY2P::updateGame(gameState);

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

		case GAME_STATES::GAME_STATES::ONE_PLAYER_MODE:
			GAMEPLAY1P::drawGame();
			break;

		case GAME_STATES::GAME_STATES::TWO_PLAYER_MODE:
			GAMEPLAY2P::drawGame();
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
		GAMEPLAY1P::unInitGame();
		CloseWindow();
	}

}