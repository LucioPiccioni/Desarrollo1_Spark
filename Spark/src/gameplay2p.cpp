#include "gameplay2p.h"

#include <List>

#include "raylib.h"

#include "scene_manager.h"
#include "obstacle.h"
#include "Button.h"
#include "state_machine.h"
#include "game_data.h"
#include "sprites.h"

namespace GAMEPLAY_2P
{
	const int maxPlayers = 2;

	PLAYER::Player player[maxPlayers];

	std::list<Obstacle::Obstacle> obstacles;

	bool shouldReset = 0;

	void initializeGame()
	{
		for (int i = 0; i < maxPlayers; i++)
		{
			initializePlayer(player[i], SPRITES::sprites.windEffect);
		}

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

		SPRITES::updateTexturesPos(deltaTime);

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

		for (int i = 0; i < maxPlayers; i++)
		{
			if (AddPoint(player[i].pos))
				player[i].points++;
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			if (DidPlayerDied(player[i].pos, player[i].radius))
				gameState.actual = GAME_STATES::Gamestate::GAME_OVER;
		}
	}

	void drawGame()
	{
		SPRITES::drawBackgroundAssets();

		for (int i = 0; i < maxPlayers; i++)
		{
			drawPlayer(player[i], SPRITES::sprites.windEffect, SPRITES::sprites.playerSprite);
		}

		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			Obstacle::drawObstacle(*it, SPRITES::sprites.pipeImage);
		}

		SPRITES::drawFrontAssets();


		std::string text = "Points: " + std::to_string(player[0].points) + ".";
		DrawText(text.c_str(), 0, 0, (int)BUTTON::scoreFontSize, BLACK);

	}

	void updatePlayer(float deltaTime)
	{

		if (IsKeyPressed(KEY_W))
		{
			movePlayerUp(player[0]);
		}

		if (IsKeyPressed(KEY_UP))
		{
			movePlayerUp(player[1]);
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			movePlayerDown(player[i], deltaTime);
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			PLAYER::Anitmation(player[i], SPRITES::sprites.playerSprite, deltaTime);
		}
	}

	bool AddPoint(Vector2 pos)
	{
		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
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


		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
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
