#pragma once

#include "raylib.h"

#include "sprites.h"
#include "state_machine.h"
#include "player.h"

namespace GAMEPLAY_1P
{
	void initializeGame();

	void resetObstacles();

	void updateGame(GAME_STATES::ProgramState& gameState);

	void updatePlayer(float deltaTime);

	void updateTexturesPos(float deltaTime);

	bool DidPlayerDied();

	void drawGame();

	bool AddPoint();
}