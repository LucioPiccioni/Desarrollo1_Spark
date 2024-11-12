
#include "gameplay.h"
#include "scene_manager.h"
#include "obstacle.h"

#include <List>

#include "state_machine.h"
#include "game_data.h"
#include "player.h"

#include "raylib.h"

#include "raylib.h"


namespace GamePlay
{

	static Player::Player player;
	std::list<Obstacle::Obstacle> obstacles;

	static void updatePlayer(float deltaTime);
	static void checkCollisionRectRect();


	void initializeGame(GAME_STATES::GAME_STATES& gameState)
	{
		initializePlayer(player);
		Obstacle::initializeObstacle(obstacle);
	}

	void updateGame(GAME_STATES::GAME_STATES& gameState)
	{
		updatePlayer();
		updateObstacle(obstacle);
		checkCollisionRectRect();
	}

	void drawGame()
	{
		DrawText("Spark v0.1", 10, 10, 20, LIGHTGRAY);
		drawPlayer(player);
		Obstacle::drawObstacle(obstacle);
	}

	void closeGame()
	{
		gameState.nextState = GAME_STATES::GAME_STATES::MENU;
	}

	static void updatePlayer(float deltaTime)
	{
		movePlayerDown(player, deltaTime);

		if (IsKeyPressed(KEY_UP))
		{
			movePlayerUp(player);
		}
	}

	static void checkCollisionRectRect()
	{
		for (const auto& pipe : obstacles)
		{
			float closestX = std::max(pipe.top.rect.x, std::min(player.pos.x, pipe.top.rect.x + pipe.top.rect.width));
			float closestY = std::max(pipe.top.rect.y, std::min(player.pos.y, pipe.top.rect.y + pipe.top.rect.height));

			float distanceX = player.pos.x - closestX;
			float distanceY = player.pos.y - closestY;

			if ((distanceX * distanceX + distanceY * distanceY) <= (player.radius * player.radius))
			{
				player.collide = true;
				break;
			}

			closestX = std::max(pipe.bottom.rect.x, std::min(player.pos.x, pipe.bottom.rect.x + pipe.bottom.rect.width));
			closestY = std::max(pipe.bottom.rect.y, std::min(player.pos.y, pipe.bottom.rect.y + pipe.bottom.rect.height));

			distanceX = player.pos.x - closestX;
			distanceY = player.pos.y - closestY;

			if ((distanceX * distanceX + distanceY * distanceY) <= (player.radius * player.radius))
			{
				player.collide = true;
				break;
			}
		}
	}

} //namespace spark_luchelli