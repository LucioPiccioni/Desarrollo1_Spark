#pragma once

#include "raylib.h"

namespace SPRITES
{
	struct SpriteMovement
	{
		float sky = 0.0f;
		float backBuildings = 0.0f;
		float fence = 0.0f;
		float frontBuildings = 0.0f;
	};

	struct Sprites
	{
		Texture2D playerSheet;
		Texture2D pipeImage;

		Texture2D sky;
		Texture2D backBuildings;
		Texture2D frontBuildings;
		Texture2D fence;
	};

	extern Sprites sprites;

	void initSprites();
	void unloadSprites();

}