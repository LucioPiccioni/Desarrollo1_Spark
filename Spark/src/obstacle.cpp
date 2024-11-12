#include "obstacle.h"
#include "game_data.h"

#include "raylib.h"
#include <list>

namespace Obstacle
{

	Obstacle Creator()
	{
		PipeSet newPipeSet = {};

		const float pipeWidth = 80;
		const float pipeHeight = screenHeight;

		newPipeSet.top.rect.x = screenWidth + newPipeSet.top.rect.width;

		newPipeSet.top.angle = 180 * (PI / 180.0f);

#pragma warning(disable:4244)
		newPipeSet.top.rect.y = rand() % (static_cast<int>(screenHeight - actualSpacing)) - pipeHeight;
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
		obstacles.top.rect.x -= obstacle.speed * deltaTime;
		obstacles.bottom.rect.x = obstacle.top.rect.x;
	}

	void drawObstacle(std::list<Obstacle>& obstacles, Texture2D& pipeTexture)
	{
		for (std::list<Obstacle>::iterator pipeSetIt = obstacle.begin(); pipeSetIt != obstacle.end(); pipeSetIt++)
		{
			DrawRectangleRec(pipeSetIt->top.rect, GREEN);
			DrawRectangleRec(pipeSetIt->bottom.rect, RED);

			pipeSetIt->top.rect.x += pipeSetIt->top.rect.width / 2;
			pipeSetIt->top.rect.y += pipeSetIt->top.rect.height / 2;

			float pipeSpriteWidth = static_cast<float>(pipeTexture.width);
			float pipeSpriteHeight = static_cast<float>(pipeTexture.height);

			DrawTexturePro(
				pipeTexture,
				Rectangle{ 0,0, pipeSpriteWidth, pipeSpriteHeight },
				pipeSetIt->top.rect,
				Vector2{ pipeSetIt->top.rect.width / 2, pipeSetIt->top.rect.height / 2 },
				180.0f,
				WHITE);

			DrawTexturePro(
				pipeTexture,
				Rectangle{ 0,0,pipeSpriteWidth, pipeSpriteHeight },
				pipeSetIt->bottom.rect,
				Vector2{ 0,0 },
				pipeSetIt->bottom.angle,
				WHITE);
		}
	}

	void relocateObstacle(std::list<Obstacle>& obstacles)
	{
		if (!obstacle.empty())
		{
			for (std::list<Obstacle>::iterator pipeSetIt = obstacles.begin(); pipeSetIt != obstacles.end(); pipeSetIt++)
			{
				if (pipeSetIt->top.rect.x + pipeSetIt->top.rect.width <= 0.0f)
				{
					obstacle.erase(pipeSetIt);
					break;
				}
			}
		}
	}

}