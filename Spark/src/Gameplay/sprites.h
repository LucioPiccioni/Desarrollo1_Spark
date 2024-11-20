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
		Texture2D playerSprite;
		Texture2D windEffect;
		Texture2D pipeImage;

		Texture2D sky;
		Texture2D backBuildings;
		Texture2D frontBuildings;
		Texture2D fence;
	};

	extern Sprites sprites;
	extern SpriteMovement spritesMovement;

	void initSprites();
	void unloadSprites();

	void updateTexturesPos(float deltaTime);

	void drawBackgroundAssets();
	void drawFrontAssets();

}