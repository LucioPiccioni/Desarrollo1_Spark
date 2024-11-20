#pragma once

namespace GAME_STATES
{
	enum class Gamestate
	{
		NONE,
		MAIN_MENU,
		ONE_PLAYER_MODE,
		TWO_PLAYER_MODE,
		RULES,
		CREDITS,
		WANT_TO_EXIT,

		PAUSE,
		GAME_OVER,
		REPLAY,

		RESUME,

		CONFIRM_EXIT,
		CANCEL_EXIT,
		EXIT
	};

	struct ProgramState
	{
		Gamestate actual = Gamestate::MAIN_MENU;
		Gamestate previusGameMode = Gamestate::MAIN_MENU;
		Gamestate previusHud = Gamestate::MAIN_MENU;
	};
}


