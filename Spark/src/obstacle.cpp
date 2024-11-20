#include "obstacle.h"

#include "raylib.h"

#include "game_data.h"

namespace OBSTACLE
{
	float actualSpeed = minSpeed;

	float actualSpacing = maxSpacing;

	float actualSpawiningTime = maxSpawiningTime;
	float spawnTimer = 0.0f;

	Obstacle Creator()
	{
		Obstacle newPipeSet = {};

		const float pipeWidth = 80;
		const float pipeHeight = SCREEN_HEIGHT;

		newPipeSet.top.rect.x = SCREEN_WIDTH + newPipeSet.top.rect.width;

		newPipeSet.top.angle = 180 * (PI / 180.0f);

#pragma warning(disable:4244)
		newPipeSet.top.rect.y = rand() % (static_cast<int>(SCREEN_HEIGHT - actualSpacing)) - pipeHeight;
#pragma warning(default:4244)

		newPipeSet.bottom.rect.x = newPipeSet.top.rect.x;
		newPipeSet.bottom.rect.y = newPipeSet.top.rect.y + pipeHeight + actualSpacing;


		newPipeSet.top.rect.width = pipeWidth;
		newPipeSet.bottom.rect.width = pipeWidth;

		newPipeSet.top.rect.height = pipeHeight;
		newPipeSet.bottom.rect.height = pipeHeight;

		return newPipeSet;
	}

	void updateObstacle(Obstacle& obstacles, float deltaTime)
	{
		obstacles.top.rect.x -= actualSpeed * deltaTime;
		obstacles.bottom.rect.x = obstacles.top.rect.x;
	}

	void drawObstacle(Obstacle obstacle, Texture2D& pipeTexture)
	{
		obstacle.top.rect.x += obstacle.top.rect.width / 2;
		obstacle.top.rect.y += obstacle.top.rect.height / 2;

		float pipeSpriteWidth = static_cast<float>(pipeTexture.width);
		float pipeSpriteHeight = static_cast<float>(pipeTexture.height);

		DrawTexturePro(
			pipeTexture,
			Rectangle{ 0,0, pipeSpriteWidth, pipeSpriteHeight },
			obstacle.top.rect,
			Vector2{ obstacle.top.rect.width / 2, obstacle.top.rect.height / 2 },
			180.0f,
			WHITE);

		DrawTexturePro(
			pipeTexture,
			Rectangle{ 0,0,pipeSpriteWidth, pipeSpriteHeight },
			obstacle.bottom.rect,
			Vector2{ 0,0 },
			obstacle.bottom.angle,
			WHITE);
	}

	bool relocateObstacle(Obstacle& obstacle)
	{
		return (obstacle.top.rect.x + obstacle.top.rect.width <= 0.0f);
	}

}