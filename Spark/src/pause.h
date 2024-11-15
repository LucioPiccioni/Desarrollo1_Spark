#pragma once

#include "raylib.h"

#include "gameplay.h"
#include "state_machine.h"

namespace PAUSE
{
	void initButtons();

	void update(GAME_STATES::GAME_STATES& gameState);

	void draw(Font font);
}