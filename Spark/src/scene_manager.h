#pragma once

#include "state_machine.h"

namespace SCENE_MANAGER
{
	extern GAME_STATES::GAME_STATES gameState;
	
	void runProgram();

	void initialize();

	void update();

	void draw();

	void close();

}




