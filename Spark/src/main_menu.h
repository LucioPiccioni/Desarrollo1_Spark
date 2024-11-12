#pragma once

#include "state_machine.h"

namespace MAIN_MENU
{

	void initializeMenu(GAME_STATES::GAME_STATES& gameState);

	void updateMenu(GAME_STATES::GAME_STATES& gameState);

	static void initializeButtons();

	void drawMenu();

}

