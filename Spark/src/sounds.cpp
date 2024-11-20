#include "sounds.h"

namespace SOUNDS
{
	GameSounds gameSounds = {};

	void init()
	{
		gameSounds.button = LoadSound("res/soundEffects/button.wav");
		gameSounds.jump  = LoadSound("res/soundEffects/jump.wav");
		gameSounds.point = LoadSound("res/soundEffects/point.wav");
		gameSounds.die = LoadSound("res/soundEffects/loose.wav");
	}

	void unInit()
	{
		UnloadSound(gameSounds.button);
		UnloadSound(gameSounds.jump);
		UnloadSound(gameSounds.point);
		UnloadSound(gameSounds.die);
	}
}
