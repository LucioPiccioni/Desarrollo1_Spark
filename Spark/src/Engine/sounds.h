#pragma once
#include "raylib.h"

namespace SOUNDS
{
	struct GameSounds
	{
		Sound button = {};
		Sound jump = {};
		Sound point = {};
		Sound die = {};
	};

	extern GameSounds gameSounds;

	void init();
	void unInit();
}