#include "gameplay.h"

#include <List>

#include "raylib.h"

#include "scene_manager.h"
#include "Button.h"

#include "obstacle.h"
#include "state_machine.h"
#include "game_data.h"

#include "sprites.h"
#include "sounds.h"

namespace GAMEPLAY_1P
{
	const int pointsPerDifficultyIncrease = 3;

	PLAYER::Player player;

	std::list<OBSTACLE::Obstacle> obstacles;

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
		OBSTACLE::actualSpacing = OBSTACLE::maxSpacing;
		OBSTACLE::actualSpeed = OBSTACLE::minSpeed;
		OBSTACLE::actualSpawiningTime = OBSTACLE::maxSpawiningTime;
		OBSTACLE::spawnTimer = 0;
	}

	void updateGame(GAME_STATES::ProgramState& gameState)
	{
		if (IsKeyPressed(KEY_ESCAPE))
			gameState.actual = GAME_STATES::Gamestate::PAUSE;

		float deltaTime = GetFrameTime();

		updatePlayer(deltaTime);

		updateTexturesPos(deltaTime);

		if (OBSTACLE::spawnTimer <= 0)
		{
			obstacles.push_back(OBSTACLE::Creator());
			OBSTACLE::spawnTimer = OBSTACLE::actualSpawiningTime;
		}
		else
			OBSTACLE::spawnTimer -= deltaTime;

		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			OBSTACLE::updateObstacle(*it, deltaTime);
		}

		if (AddPoint())
		{
			StopSound(SOUNDS::gameSounds.point);
			PlaySound(SOUNDS::gameSounds.point);
			player.points++;
			player.EXP++;
		}

		increaseDifficulty();

		if (DidPlayerDied())
		{
			StopSound(SOUNDS::gameSounds.die);
			PlaySound(SOUNDS::gameSounds.die);
			gameState.actual = GAME_STATES::Gamestate::GAME_OVER;
		}
	}

	void increaseDifficulty()
	{
		if (player.EXP == pointsPerDifficultyIncrease)
		{
			player.incrisingDificulty = true;
			player.EXP = 0;
		}

		if (player.incrisingDificulty)
		{
			if (OBSTACLE::actualSpeed < OBSTACLE::maxSpeed)
			{
				OBSTACLE::actualSpeed += OBSTACLE::actualSpeed * 0.15f;
			}

			if (OBSTACLE::actualSpacing > OBSTACLE::minSpacing)
			{
				OBSTACLE::actualSpacing -= OBSTACLE::actualSpacing * 0.10f;
			}

			if (OBSTACLE::actualSpawiningTime > OBSTACLE::minSpawiningTime)
			{
				OBSTACLE::actualSpawiningTime -= OBSTACLE::actualSpawiningTime * 0.10f;
			}

			player.incrisingDificulty = false;
		}
	}

	void drawGame()
	{
		std::string text = "Points: " + std::to_string(player.points) + ".";

		SPRITES::drawBackgroundAssets();

		drawPlayer(player, SPRITES::sprites.windEffect, SPRITES::sprites.playerSprite);

		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			OBSTACLE::drawObstacle(*it, SPRITES::sprites.pipeImage);
		}

		SPRITES::drawFrontAssets();

		DrawText(text.c_str(), 0, 0, static_cast<int>(BUTTON::scoreFontSize), BLACK);
	}

	void updatePlayer(float deltaTime)
	{
		movePlayerDown(player, deltaTime);

		if (IsKeyPressed(KEY_SPACE))
		{
			movePlayerUp(player);

			StopSound(SOUNDS::gameSounds.jump);
			PlaySound(SOUNDS::gameSounds.jump);
		}

		PLAYER::moveAngleUp(player, deltaTime);
		PLAYER::Anitmation(player, SPRITES::sprites.windEffect, deltaTime);
	}

	void updateTexturesPos(float deltaTime)
	{
		SPRITES::spritesMovement.sky -= (OBSTACLE::actualSpeed * 0.05f) * deltaTime;
		SPRITES::spritesMovement.backBuildings -= (OBSTACLE::actualSpeed - 90) * deltaTime;
		SPRITES::spritesMovement.frontBuildings -= (OBSTACLE::actualSpeed - 50) * deltaTime;
		SPRITES::spritesMovement.fence -= (OBSTACLE::actualSpeed + 100) * deltaTime;

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
		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
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


		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
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