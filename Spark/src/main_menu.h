#pragma once

#include "state_machine.h"

namespace MAIN_MENU
{

	void initializeMenu();

	void updateMenu(GAME_STATES::ProgramState& gameState);

	void initializeButtons();

	void drawMenu();

}

