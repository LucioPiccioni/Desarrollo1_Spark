#pragma once

#include "state_machine.h"

namespace GamePlay
{

	void initializeGame(GAME_STATES::GAME_STATES& gameState);

	void updateGame(GAME_STATES::GAME_STATES& gameState);

	void drawGame();

	void closeGame();

} 