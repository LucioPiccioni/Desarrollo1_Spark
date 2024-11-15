#pragma once

#include "raylib.h"

#include "gameplay.h"
#include "state_machine.h"

namespace PAUSE
{
	void initButtons();

	void update(GAME_STATES::ProgramState& gameState);

	void draw(Font font);
}