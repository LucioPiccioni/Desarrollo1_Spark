#include "raylib.h"

#include "state_machine.h"

namespace CREDITS_MENU
{
	struct Credit
	{
		const char* text;
		const char* url;
		Rectangle buttonRect;
	};

	void initializeCreditsMenu();

	void updateCreditsMenu(GAME_STATES::Gamestate& programState);

	void drawCreditsMenu(Font font);
}