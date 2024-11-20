#include "raylib.h"

#include "state_machine.h"

namespace RULES_MENU
{
	void initializeRulesMenu();

	void updateRulesMenu(GAME_STATES::Gamestate& programState);

	void drawRulesMenu(Font font);
}