#pragma once

#include "raylib.h"

#include "sprites.h"
#include "state_machine.h"
#include "player.h"

namespace GAMEPLAY
{
	extern Sprites::Sprites sprites;

	void initializeGame();

	void resetObstacles();

	void updateGame(GAME_STATES::GAME_STATES& gameState);

	void updatePlayer(float deltaTime);

	void updateTexturesPos(float deltaTime);

	bool DidPlayerDied();

	void drawGame();

	void drawBackgroundAssets();

	void drawFrontAssets();

	bool AddPoint();

	void unInitGame();

}