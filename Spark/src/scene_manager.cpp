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
	GAME_STATES::ProgramState programState;

	void runProgram()
	{
		initialize();

		while (!WindowShouldClose() && programState.actual != GAME_STATES::Gamestate::EXIT)
		{
			update();

			draw();
		}

		close();
	}

	void initialize()
	{
		InitWindow(800, 600, "Flappy Bird");

		programState.actual = GAME_STATES::Gamestate::MAIN_MENU;
		programState.previus = GAME_STATES::Gamestate::NONE;

		SPRITES::initSprites();
		GAMEPLAY_1P::initializeGame();
		GAMEPLAY_2P::initializeGame();
		MAIN_MENU::initializeMenu();
		PAUSE::initButtons();
		GAME_OVER::initButtons();

		SetExitKey(0);
	}

	void update()
	{
		switch (programState.actual)
		{
		case GAME_STATES::Gamestate::MAIN_MENU:
			MAIN_MENU::updateMenu(programState);
			break;

		case GAME_STATES::Gamestate::ONE_PLAYER_MODE:
			programState.previus = GAME_STATES::Gamestate::ONE_PLAYER_MODE;
			GAMEPLAY_1P::updateGame(programState);
			break;

		case GAME_STATES::Gamestate::TWO_PLAYER_MODE:
			programState.previus = GAME_STATES::Gamestate::TWO_PLAYER_MODE;
			GAMEPLAY_2P::updateGame(programState);
			break;

		case GAME_STATES::Gamestate::PAUSE:
			PAUSE::update(programState);
			break;

		case GAME_STATES::Gamestate::GAME_OVER:
			GAME_OVER::update(programState);
			break;

		case GAME_STATES::Gamestate::RULES:
			break;

		case GAME_STATES::Gamestate::CREDITS:
			break;

		case GAME_STATES::Gamestate::WANT_TO_EXIT:
			break;

		default:
			break;
		}
	}

	void draw()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (programState.actual)
		{
		case GAME_STATES::Gamestate::MAIN_MENU:
			MAIN_MENU::drawMenu();
			break;

		case GAME_STATES::Gamestate::ONE_PLAYER_MODE:
			GAMEPLAY_1P::drawGame();
			break;

		case GAME_STATES::Gamestate::TWO_PLAYER_MODE:
			GAMEPLAY_2P::drawGame();
			break;

		case GAME_STATES::Gamestate::PAUSE:
			PAUSE::draw(GetFontDefault());
			break;

		case GAME_STATES::Gamestate::GAME_OVER:
			GAME_OVER::draw(GetFontDefault());
			break;

		case GAME_STATES::Gamestate::RULES:
			break;

		case GAME_STATES::Gamestate::CREDITS:
			break;

		case GAME_STATES::Gamestate::WANT_TO_EXIT:
			break;

		default:
			break;
		}


		EndDrawing();
	}

	void close()
	{
		SPRITES::unloadSprites();
		CloseWindow();
	}

}