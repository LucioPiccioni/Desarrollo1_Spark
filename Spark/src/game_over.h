#pragma once

#include "state_machine.h"
#include "raylib.h"

namespace GAME_OVER
{
	void initButtons();

	void update(GAME_STATES::GAME_STATES& gameState);

	void draw(Font font);
}