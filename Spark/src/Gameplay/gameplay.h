#pragma once

#include "raylib.h"

#include "Gameplay/sprites.h"
#include "Engine/state_machine.h"
#include "Gameplay/player.h"

namespace GAMEPLAY_1P
{
	void initializeGame();

	void resetObstacles();

	void updateGame(GAME_STATES::ProgramState& gameState);

	void increaseDifficulty();

	void updatePlayer(float deltaTime);

	void updateTexturesPos(float deltaTime);

	bool DidPlayerDied();

	void drawGame();

	bool AddPoint();
}