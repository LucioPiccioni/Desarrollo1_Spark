#include "gameplay.h"

#include <List>

#include "raylib.h"

#include "scene_manager.h"
#include "obstacle.h"
#include "Button.h"
#include "state_machine.h"
#include "game_data.h"
#include "sprites.h"

namespace GAMEPLAY_1P
{
	PLAYER::Player player;

	std::list<Obstacle::Obstacle> obstacles;

	bool shouldReset = 0;

	void initializeGame()
	{
		initializePlayer(player, SPRITES::sprites.windEffect);
		resetObstacles();
	}

	void resetObstacles()
	{
		SPRITES::spritesMovement = { 0,0,0,0 };
		obstacles.clear();
		Obstacle::actualSpacing = Obstacle::maxSpacing;
		Obstacle::actualSpeed = Obstacle::minSpeed;
		Obstacle::spawnTimer = 0;
	}

	void updateGame(GAME_STATES::ProgramState& gameState)
	{
		if (IsKeyPressed(KEY_ESCAPE))
			gameState.actual = GAME_STATES::Gamestate::PAUSE;

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
			gameState.actual = GAME_STATES::Gamestate::GAME_OVER;
	}

	void drawGame()
	{
		std::string text = "Points: " + std::to_string(player.points) + ".";

		SPRITES::drawBackgroundAssets();

		drawPlayer(player, SPRITES::sprites.windEffect, SPRITES::sprites.playerSprite);

		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			Obstacle::drawObstacle(*it, SPRITES::sprites.pipeImage);
		}

		SPRITES::drawFrontAssets();

		DrawText(text.c_str(), 0, 0, (int)BUTTON::scoreFontSize, BLACK);
	}

	void updatePlayer(float deltaTime)
	{
		movePlayerDown(player, deltaTime);

		if (IsKeyPressed(KEY_SPACE))
		{
			movePlayerUp(player);
		}

		PLAYER::Anitmation(player, SPRITES::sprites.windEffect, deltaTime);
	}

	void updateTexturesPos(float deltaTime)
	{
		SPRITES::spritesMovement.sky -= (Obstacle::actualSpeed * 0.05f) * deltaTime;
		SPRITES::spritesMovement.backBuildings -= (Obstacle::actualSpeed - 90) * deltaTime;
		SPRITES::spritesMovement.frontBuildings -= (Obstacle::actualSpeed - 50) * deltaTime;
		SPRITES::spritesMovement.fence -= (Obstacle::actualSpeed + 100) * deltaTime;

		if (SPRITES::spritesMovement.sky <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.sky = 0;

		if (SPRITES::spritesMovement.backBuildings <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.backBuildings = 0;

		if (SPRITES::spritesMovement.frontBuildings <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.frontBuildings = 0;

		if (SPRITES::spritesMovement.fence <= -SCREEN_WIDTH)
			SPRITES::spritesMovement.fence = 0;
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