#include "player.h"

#include "raylib.h"

#include "game_data.h"

namespace PLAYER
{
	void initializePlayer(Player& player, Texture2D& playerSheet)
	{
		player.pos = { SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 };
		player.frameRec = { 0.0f, 0.0f, (float)playerSheet.width / 3, (float)playerSheet.height };
		player.size = 64;
		player.radius = player.size / 2;

		player.jumpForce = -300;
		player.gravityValue = 500;

		player.points = 0;

		player.speed = 0;
		player.animate = false;
	}

	void resetPlayer(Player& player)
	{
		player.pos = { SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 };
	}

	void movePlayerUp(Player& player)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			player.speed = player.jumpForce;
			player.animate = true;
		}
	}

	void Anitmation(Player& player, Texture2D& playerSheet, float deltaTime)
	{
		if (player.animate)
		{
			player.framesCounter += deltaTime;

			const float frameDuration = 0.12f;

			if (player.framesCounter >= frameDuration)
			{
				player.framesCounter -= frameDuration;
				player.currentFrame++;

				if (player.currentFrame > 2)
				{
					player.currentFrame = 0;
					player.animate = false;
				}

				player.frameRec.x = static_cast<float>(player.currentFrame) * (playerSheet.width / 3.0f);
			}
		}
	}

	void movePlayerDown(Player& player, float deltaTime)
	{
		player.speed += player.gravityValue * deltaTime;
		player.pos.y += player.speed * deltaTime;
	}

	void drawPlayer(Player player, Texture2D& playerSheet)
	{
		player.pos.x += playerSheet.width / 2;
		player.pos.y += playerSheet.height / 2;

		DrawTexturePro(
			playerSheet,
			player.frameRec,
			Rectangle{ player.pos.x - player.size / 2, player.pos.y - player.size / 2, player.size, player.size },
			Vector2{ static_cast<float>(playerSheet.width) / 2, static_cast<float>(playerSheet.height) / 2 },
			0,
			WHITE);
	}

}