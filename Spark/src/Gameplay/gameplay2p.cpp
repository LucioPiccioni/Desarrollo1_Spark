#include "gameplay2p.h"

#include <List>

#include "raylib.h"

#include "Engine/scene_manager.h"
#include "Menus/Button.h"

#include "Gameplay/obstacle.h"
#include "Engine/state_machine.h"
#include "Engine/game_data.h"

#include "Gameplay/sprites.h"
#include "Engine/sounds.h"

namespace GAMEPLAY_2P
{
	const int pointsPerDifficultyIncrease = 3;

	const int maxPlayers = 2;

	PLAYER::Player player[maxPlayers];

	std::list<OBSTACLE::Obstacle> obstacles;

	bool shouldReset = 0;

	void initializeGame()
	{
		for (int i = 0; i < maxPlayers; i++)
		{
			initializePlayer(player[i], SPRITES::sprites.windEffect);
		}

		player[0].color = PURPLE;
		player[1].color = SKYBLUE;

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

		SPRITES::updateTexturesPos(deltaTime);

		if (OBSTACLE::spawnTimer <= 0)
		{
			obstacles.push_back(OBSTACLE::Creator());
			OBSTACLE::spawnTimer = 6;
		}
		else
			OBSTACLE::spawnTimer -= deltaTime;

		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			OBSTACLE::updateObstacle(*it, deltaTime);
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			if (AddPoint(player[i].pos))
			{
				StopSound(SOUNDS::gameSounds.point);
				PlaySound(SOUNDS::gameSounds.point);
				player[i].points++;
			}
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			if (DidPlayerDied(player[i].pos, player[i].radius))
			{
				StopSound(SOUNDS::gameSounds.die);
				PlaySound(SOUNDS::gameSounds.die);
				gameState.actual = GAME_STATES::Gamestate::GAME_OVER;
			}
		}
	}

	void increaseDifficulty()
	{
		if (player[0].EXP == pointsPerDifficultyIncrease)
		{
			player[0].incrisingDificulty = true;
			player[0].EXP = 0;
		}

		if (player[0].incrisingDificulty)
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

			player[0].incrisingDificulty = false;
		}
	}

	void drawGame()
	{
		SPRITES::drawBackgroundAssets();

		for (int i = 0; i < maxPlayers; i++)
		{
			drawPlayer(player[i], SPRITES::sprites.windEffect, SPRITES::sprites.playerSprite);
		}

		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			OBSTACLE::drawObstacle(*it, SPRITES::sprites.pipeImage);
		}

		SPRITES::drawFrontAssets();


		std::string text = "Points: " + std::to_string(player[0].points) + ".";
		DrawText(text.c_str(), 0, 0, static_cast<int>(BUTTON::scoreFontSize), BLACK);

	}

	void updatePlayer(float deltaTime)
	{

		if (IsKeyPressed(KEY_W))
		{
			StopSound(SOUNDS::gameSounds.jump);
			PlaySound(SOUNDS::gameSounds.jump);
			movePlayerUp(player[0]);
		}

		if (IsKeyPressed(KEY_UP))
		{
			StopSound(SOUNDS::gameSounds.jump);
			PlaySound(SOUNDS::gameSounds.jump);
			movePlayerUp(player[1]);
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			movePlayerDown(player[i], deltaTime);

			PLAYER::moveAngleUp(player[i], deltaTime);
			PLAYER::Anitmation(player[i], SPRITES::sprites.windEffect, deltaTime);
		}

	}

	bool AddPoint(Vector2 pos)
	{
		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			if (!it->counted && pos.x > it->top.rect.x)
			{
				it->counted = true;
				return true;
			}
		}

		return false;
	}

	bool DidPlayerDied(Vector2 pos, float radius)
	{
		if (pos.y + radius > SCREEN_HEIGHT)
			return true;


		for (std::list<OBSTACLE::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			float closestX = std::max(it->top.rect.x, std::min(pos.x, it->top.rect.x + it->top.rect.width));
			float closestY = std::max(it->top.rect.y, std::min(pos.y, it->top.rect.y + it->top.rect.height));

			float distanceX = pos.x - closestX;
			float distanceY = pos.y - closestY;

			if ((distanceX * distanceX + distanceY * distanceY) <= (radius * radius) ||
				pos.y - radius < it->top.rect.y && pos.x + radius > it->top.rect.x && pos.x - radius < it->top.rect.x + it->top.rect.width)
			{
				return true;
			}

			closestX = std::max(it->bottom.rect.x, std::min(pos.x, it->bottom.rect.x + it->bottom.rect.width));
			closestY = std::max(it->bottom.rect.y, std::min(pos.y, it->bottom.rect.y + it->bottom.rect.height));

			distanceX = pos.x - closestX;
			distanceY = pos.y - closestY;

			if ((distanceX * distanceX + distanceY * distanceY) <= (radius * radius))
			{
				return true;
			}
		}

		return false;
	}
}
