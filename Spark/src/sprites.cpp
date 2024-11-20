#include "sprites.h"
#include "obstacle.h"
#include "game_data.h"

namespace SPRITES
{
	Sprites sprites = {};
	SpriteMovement spritesMovement = {};

	void initSprites()
	{
		sprites.playerSprite = LoadTexture("res/Paper Plane.png");
		sprites.windEffect = LoadTexture("res/Wind Effect2.png");
		sprites.pipeImage = LoadTexture("res/pipe.png");

		sprites.sky = LoadTexture("res/Paralax/evening sky.png");
		sprites.backBuildings = LoadTexture("res/Paralax/evening buildings back.png");
		sprites.frontBuildings = LoadTexture("res/Paralax/evening buildings front.png");
		sprites.fence = LoadTexture("res/Paralax/night fence.png");
	}

	void unloadSprites()
	{
		UnloadTexture(sprites.windEffect);
		UnloadTexture(sprites.pipeImage);

		UnloadTexture(sprites.backBuildings);
		UnloadTexture(sprites.frontBuildings);
		UnloadTexture(sprites.fence);
	}

	void updateTexturesPos(float deltaTime)
	{
		float skySpeed = (OBSTACLE::actualSpeed * 0.05f) * deltaTime;
		float backBuildingSpeed = (OBSTACLE::actualSpeed - 90) * deltaTime;
		float frontBuildingSpeed = (OBSTACLE::actualSpeed - 50) * deltaTime;
		float fenceSpeed = (OBSTACLE::actualSpeed + 100) * deltaTime;

		if (skySpeed > 0)
			SPRITES::spritesMovement.sky -= skySpeed;

		if (backBuildingSpeed > 0)
			SPRITES::spritesMovement.backBuildings -= backBuildingSpeed;

		if (frontBuildingSpeed > 0)
			SPRITES::spritesMovement.frontBuildings -= frontBuildingSpeed;

		if (fenceSpeed > 0)
			SPRITES::spritesMovement.fence -= fenceSpeed;


		if (SPRITES::spritesMovement.sky <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.sky = 0;

		if (SPRITES::spritesMovement.backBuildings <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.backBuildings = 0;

		if (SPRITES::spritesMovement.frontBuildings <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.frontBuildings = 0;

		if (SPRITES::spritesMovement.fence <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.fence = 0;
	}

	void drawBackgroundAssets()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(SPRITES::sprites.sky.width), static_cast<float>(SPRITES::sprites.sky.height) };

		Rectangle destRec = { SPRITES::spritesMovement.sky, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(SPRITES::sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + SPRITES::spritesMovement.sky, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(SPRITES::sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);


		sourceRec = { 0.0f, 0.0f, static_cast<float>(SPRITES::sprites.backBuildings.width), static_cast<float>(SPRITES::sprites.backBuildings.height) };

		destRec = { SPRITES::spritesMovement.backBuildings, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(SPRITES::sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + SPRITES::spritesMovement.backBuildings, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(SPRITES::sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);


		sourceRec = { 0.0f, 0.0f, static_cast<float>(SPRITES::sprites.frontBuildings.width), static_cast<float>(SPRITES::sprites.frontBuildings.height) };

		destRec = { SPRITES::spritesMovement.frontBuildings, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(SPRITES::sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + SPRITES::spritesMovement.frontBuildings, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(SPRITES::sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);
	}

	void drawFrontAssets()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(SPRITES::sprites.fence.width), static_cast<float>(SPRITES::sprites.fence.height) };

		Rectangle destRec = { SPRITES::spritesMovement.fence, static_cast<float>(SCREEN_HEIGHT) - SPRITES::sprites.fence.height * 2, SCREEN_WIDTH * 2, static_cast<float>(SPRITES::sprites.fence.height) * 2 };
		DrawTexturePro(SPRITES::sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + SPRITES::spritesMovement.fence, static_cast<float>(SCREEN_HEIGHT) - SPRITES::sprites.fence.height * 2, SCREEN_WIDTH * 2, static_cast<float>(SPRITES::sprites.fence.height) * 2 };
		DrawTexturePro(SPRITES::sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);
	}
}