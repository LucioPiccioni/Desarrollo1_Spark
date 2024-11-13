#include "sprites.h"

namespace Sprites
{
	Sprites sprites = {};

	void initSprites()
	{
		sprites.playerSheet = LoadTexture("res/birdSpriteSheet.png");
		sprites.pipeImage = LoadTexture("res/pipe.png");

		sprites.sky = LoadTexture("res/Paralax/evening sky.png");
		sprites.backBuildings = LoadTexture("res/Paralax/evening buildings back.png");
		sprites.frontBuildings = LoadTexture("res/Paralax/evening buildings front.png");
		sprites.fence = LoadTexture("res/Paralax/night fence.png");
	}

	void unloadSprites()
	{
		UnloadTexture(sprites.playerSheet);
		UnloadTexture(sprites.pipeImage);

		UnloadTexture(sprites.backBuildings);
		UnloadTexture(sprites.frontBuildings);
		UnloadTexture(sprites.fence);
	}

}