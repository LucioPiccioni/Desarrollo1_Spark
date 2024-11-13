#include "gameplay.h"

#include <List>

#include "raylib.h"

#include "scene_manager.h"
#include "obstacle.h"
#include "Button.h"
#include "state_machine.h"
#include "game_data.h"
#include "sprites.h"

namespace GAMEPLAY
{
	PLAYER::Player player;

	Sprites::Sprites sprites = {};
	Sprites::SpriteMovement spriteMovement = {};

	std::list<Obstacle::Obstacle> obstacles;

	bool shouldReset = 0;

	void initializeGame()
	{
		initializePlayer(player, sprites.playerSheet);
		resetObstacles();
	}

	void resetObstacles()
	{
		obstacles.clear();
		Obstacle::actualSpacing = Obstacle::maxSpacing;
		Obstacle::actualSpeed = Obstacle::minSpeed;
		Obstacle::spawnTimer = 0;
	}

	void updateGame(GAME_STATES::GAME_STATES& gameState)
	{
		if (IsKeyPressed(KEY_ESCAPE))
			gameState = GAME_STATES::GAME_STATES::PAUSE;

		float deltaTime = GetFrameTime();

		updatePlayer(deltaTime);

		updateTexturesPos(deltaTime);

		if (Obstacle::spawnTimer <= 0)
		{
			obstacles.push_back(Obstacle::Creator());
			Obstacle::spawnTimer = 6;
		}
		else
			Obstacle::spawnTimer -= deltaTime;

		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			Obstacle::updateObstacle(*it, deltaTime);
		}

		if (AddPoint())
			player.points++;

		if (DidPlayerDied())
			gameState = GAME_STATES::GAME_STATES::GAME_OVER;
	}

	void drawGame()
	{
		std::string text = "Points: " + std::to_string(player.points) + ".";


		drawBackgroundAssets();

		drawPlayer(player, sprites.playerSheet);

		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			Obstacle::drawObstacle(*it, sprites.pipeImage);
		}

		drawFrontAssets();

		DrawText(text.c_str(), 0, 0, (int)BUTTON::scoreFontSize, BLACK);
	}

	void drawBackgroundAssets()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, (float)sprites.sky.width, (float)sprites.sky.height };

		Rectangle destRec = { spriteMovement.sky, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.sky, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);


		sourceRec = { 0.0f, 0.0f, (float)sprites.backBuildings.width, (float)sprites.backBuildings.height };

		destRec = { spriteMovement.backBuildings, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.backBuildings, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);


		sourceRec = { 0.0f, 0.0f, (float)sprites.frontBuildings.width, (float)sprites.frontBuildings.height };

		destRec = { spriteMovement.frontBuildings, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.frontBuildings, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);
	}

	void drawFrontAssets()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, (float)sprites.fence.width, (float)sprites.fence.height };

		Rectangle destRec = { spriteMovement.fence, (float)SCREEN_HEIGHT - sprites.fence.height * 2, SCREEN_WIDTH * 2, (float)sprites.fence.height * 2 };
		DrawTexturePro(sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.fence, (float)SCREEN_HEIGHT - sprites.fence.height * 2, SCREEN_WIDTH * 2, (float)sprites.fence.height * 2 };
		DrawTexturePro(sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);
	}

	void unInitGame()
	{
		Sprites::unloadSprites(sprites);
	}

	void updatePlayer(float deltaTime)
	{
		movePlayerDown(player, deltaTime);

		if (IsKeyPressed(KEY_SPACE))
		{
			movePlayerUp(player);
		}

		PLAYER::Anitmation(player, sprites.playerSheet, deltaTime);
	}

	void updateTexturesPos(float deltaTime)
	{
		spriteMovement.sky -= (Obstacle::actualSpeed * 0.05f) * deltaTime;
		spriteMovement.backBuildings -= (Obstacle::actualSpeed - 90) * deltaTime;
		spriteMovement.frontBuildings -= (Obstacle::actualSpeed - 50) * deltaTime;
		spriteMovement.fence -= (Obstacle::actualSpeed + 100) * deltaTime;

		if (spriteMovement.sky <= -SCREEN_WIDTH)
			spriteMovement.sky = 0;

		if (spriteMovement.backBuildings <= -SCREEN_WIDTH)
			spriteMovement.backBuildings = 0;

		if (spriteMovement.frontBuildings <= -SCREEN_WIDTH)
			spriteMovement.frontBuildings = 0;

		if (spriteMovement.fence <= -SCREEN_WIDTH)
			spriteMovement.fence = 0;
	}

	bool AddPoint()
	{
		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			if (!it->counted && player.pos.x > it->top.rect.x)
			{
				it->counted = true;
				return true;
			}
		}

		return false;
	}

	bool DidPlayerDied()
	{
		if (player.pos.y + player.radius > SCREEN_HEIGHT)
			return true;


		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			float closestX = std::max(it->top.rect.x, std::min(player.pos.x, it->top.rect.x + it->top.rect.width));
			float closestY = std::max(it->top.rect.y, std::min(player.pos.y, it->top.rect.y + it->top.rect.height));

			float distanceX = player.pos.x - closestX;
			float distanceY = player.pos.y - closestY;

			if ((distanceX * distanceX + distanceY * distanceY) <= (player.radius * player.radius) || 
				player.pos.y - player.radius < it->top.rect.y && player.pos.x + player.radius > it->top.rect.x && player.pos.x - player.radius < it->top.rect.x + it->top.rect.width)
			{
				return true;
			}

			closestX = std::max(it->bottom.rect.x, std::min(player.pos.x, it->bottom.rect.x + it->bottom.rect.width));
			closestY = std::max(it->bottom.rect.y, std::min(player.pos.y, it->bottom.rect.y + it->bottom.rect.height));

			distanceX = player.pos.x - closestX;
			distanceY = player.pos.y - closestY;

			if ((distanceX * distanceX + distanceY * distanceY) <= (player.radius * player.radius))
			{
				return true;
			}
		}

		return false;
	}
}