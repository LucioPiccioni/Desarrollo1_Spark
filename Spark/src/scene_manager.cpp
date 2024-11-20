#include "scene_manager.h"

#include "raylib.h"

#include "state_machine.h"

#include "sprites.h"
#include "music.h"
#include "sounds.h"
#include "button.h"

#include "player.h"

#include "main_menu.h"
#include "rules.h"
#include "gameplay.h"
#include "gameplay2p.h"
#include "credits.h"
#include "pause.h"
#include "game_over.h"

#include "confirm_exit.h"

namespace SCENE_MANAGER
{
	GAME_STATES::ProgramState programState;
	Font font;

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
		InitWindow(800, 600, "The Spark");

		InitAudioDevice();

		font = LoadFontEx("res/Fonts/Lofi Lifestyle Demo.ttf", static_cast<int>(BUTTON::titlesFontSize), 0, 0);

		programState.actual = GAME_STATES::Gamestate::MAIN_MENU;
		programState.previusGameMode = GAME_STATES::Gamestate::NONE;
		programState.previusHud = GAME_STATES::Gamestate::NONE;

		MAIN_MENU::initializeMenu();
		RULES_MENU::initializeRulesMenu();
		SPRITES::initSprites();
		SOUNDS::init();
		SOUND_TRACKS::init();
		GAMEPLAY_1P::initializeGame();
		GAMEPLAY_2P::initializeGame();
		PAUSE::initButtons();
		GAME_OVER::initButtons();
		CONFIRM_EXIT::initButtons();
		CREDITS_MENU::initializeCreditsMenu();

		SetExitKey(0);
	}

	void update()
	{
		SOUND_TRACKS::MusicControl(programState);

		switch (programState.actual)
		{
		case GAME_STATES::Gamestate::MAIN_MENU:

			programState.previusHud = GAME_STATES::Gamestate::MAIN_MENU;
			MAIN_MENU::updateMenu(programState);
			break;

		case GAME_STATES::Gamestate::ONE_PLAYER_MODE:

			programState.previusHud = GAME_STATES::Gamestate::PAUSE;
			programState.previusGameMode = GAME_STATES::Gamestate::ONE_PLAYER_MODE;
			GAMEPLAY_1P::updateGame(programState);
			break;

		case GAME_STATES::Gamestate::TWO_PLAYER_MODE:

			programState.previusHud = GAME_STATES::Gamestate::PAUSE;
			programState.previusGameMode = GAME_STATES::Gamestate::TWO_PLAYER_MODE;
			GAMEPLAY_2P::updateGame(programState);
			break;

		case GAME_STATES::Gamestate::PAUSE:

			PAUSE::update(programState);
			break;

		case GAME_STATES::Gamestate::GAME_OVER:

			programState.previusHud = GAME_STATES::Gamestate::GAME_OVER;
			GAME_OVER::update(programState);
			break;

		case GAME_STATES::Gamestate::RULES:

			RULES_MENU::updateRulesMenu(programState.actual);
			break;

		case GAME_STATES::Gamestate::CREDITS:

			CREDITS_MENU::updateCreditsMenu(programState.actual);
			break;

		case GAME_STATES::Gamestate::WANT_TO_EXIT:

			CONFIRM_EXIT::update(programState);
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
			MAIN_MENU::drawMenu(font);
			break;

		case GAME_STATES::Gamestate::ONE_PLAYER_MODE:
			GAMEPLAY_1P::drawGame();
			break;

		case GAME_STATES::Gamestate::TWO_PLAYER_MODE:
			GAMEPLAY_2P::drawGame();
			break;

		case GAME_STATES::Gamestate::PAUSE:
			PAUSE::draw(font, programState.previusGameMode);
			break;

		case GAME_STATES::Gamestate::GAME_OVER:
			GAME_OVER::draw(font);
			break;

		case GAME_STATES::Gamestate::RULES:
			RULES_MENU::drawRulesMenu(font);
			break;

		case GAME_STATES::Gamestate::CREDITS:
			CREDITS_MENU::drawCreditsMenu(font);
			break;

		case GAME_STATES::Gamestate::WANT_TO_EXIT:
			CONFIRM_EXIT::draw(font);
			break;

		default:
			break;
		}


		EndDrawing();
	}

	void close()
	{
		SPRITES::unloadSprites();
		SOUNDS::unInit();
		SOUND_TRACKS::unInit();
		UnloadFont(font);

		CloseAudioDevice();
		CloseWindow();
	}

}