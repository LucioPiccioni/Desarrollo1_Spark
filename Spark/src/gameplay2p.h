#pragma once

#include "raylib.h"

#include "sprites.h"
#include "state_machine.h"
#include "player.h"

namespace GAMEPLAY_2P
{
	void initializeGame();

	void resetObstacles();

	void updateGame(GAME_STATES::ProgramState& gameState);

	void updatePlayer(float deltaTime);

	void updateTexturesPos(float deltaTime);

	bool DidPlayerDied(Vector2 pos, float radius);

	void drawGame();

	void drawBackgroundAssets();

	void drawFrontAssets();

	bool AddPoint(Vector2 pos);

	void unInitGame();
}