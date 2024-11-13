#include "gameplay2p.h"

#include <List>

#include "raylib.h"

#include "scene_manager.h"
#include "obstacle.h"
#include "Button.h"
#include "state_machine.h"
#include "game_data.h"
#include "sprites.h"

namespace GAMEPLAY2P
{
	const int maxPlayers = 2;

	PLAYER::Player player[maxPlayers];

	Sprites::SpriteMovement spriteMovement = {};

	std::list<Obstacle::Obstacle> obstacles;

	bool shouldReset = 0;

	void initializeGame()
	{
		for (int i = 0; i < maxPlayers; i++)
		{
			initializePlayer(player[i], Sprites::sprites.playerSheet);
		}

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

		for (int i = 0; i < maxPlayers; i++)
		{
			if (AddPoint(player[i].pos))
				player[i].points++;
		}

		for (int i = 0; i < maxPlayers; i++)
		{
			if (DidPlayerDied(player[i].pos, player[i].radius))
				gameState = GAME_STATES::GAME_STATES::GAME_OVER;
		}
	}

	void drawGame()
	{
		drawBackgroundAssets();

		for (int i = 0; i < maxPlayers; i++)
		{
			drawPlayer(player[i], Sprites::sprites.playerSheet);
		}

		for (std::list<Obstacle::Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		{
			Obstacle::drawObstacle(*it, Sprites::sprites.pipeImage);
		}

		drawFrontAssets();

	
			std::string text = "Points: " + std::to_string(player[0].points) + ".";
			DrawText(text.c_str(), 0, 0, (int)BUTTON::scoreFontSize, BLACK);
		
	}

	void drawBackgroundAssets()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, (float)Sprites::sprites.sky.width, (float)Sprites::sprites.sky.height };

		Rectangle destRec = { spriteMovement.sky, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(Sprites::sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.sky, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(Sprites::sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);


		sourceRec = { 0.0f, 0.0f, (float)Sprites::sprites.backBuildings.width, (float)Sprites::sprites.backBuildings.height };

		destRec = { spriteMovement.backBuildings, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(Sprites::sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.backBuildings, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(Sprites::sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);


		sourceRec = { 0.0f, 0.0f, (float)Sprites::sprites.frontBuildings.width, (float)Sprites::sprites.frontBuildings.height };

		destRec = { spriteMovement.frontBuildings, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(Sprites::sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.frontBuildings, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
		DrawTexturePro(Sprites::sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);
	}

	void drawFrontAssets()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, (float)Sprites::sprites.fence.width, (float)Sprites::sprites.fence.height };

		Rectangle destRec = { spriteMovement.fence, (float)SCREEN_HEIGHT - Sprites::sprites.fence.height * 2, SCREEN_WIDTH * 2, (float)Sprites::sprites.fence.height * 2 };
		DrawTexturePro(Sprites::sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { SCREEN_WIDTH + spriteMovement.fence, (float)SCREEN_HEIGHT - Sprites::sprites.fence.height * 2, SCREEN_WIDTH * 2, (float)Sprites::sprites.fence.height * 2 };
		DrawTexturePro(Sprites::sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);
	}

	void unInitGame()
	{
		Sprites::unloadSprites();
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
			PLAYER::Anitmation(player[i], Sprites::sprites.playerSheet, deltaTime);
		}
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
