#include "player.h"

#include "raylib.h"

#include "game_data.h"
#include <corecrt_math.h>

namespace PLAYER
{
	const int animationTotalFrames = 6;

	void initializePlayer(Player& player, Texture2D& playerSheet)
	{
		player.pos = { SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 };
		player.frameRec = { 0.0f, 0.0f, (float)playerSheet.width / animationTotalFrames, (float)playerSheet.height };
		player.size = 64;
		player.radius = player.size * 0.5f;

		player.color = WHITE;

		player.currentFrame = 0;
		player.framesCounter = 0;

		player.jumpForce = -300;
		player.gravityValue = 500;

		player.points = 0;
		player.EXP = 0;

		player.speed = 0;

		player.animate = false;
		player.upwardsAngle = false;
		player.incrisingDificulty = false;
	}

	void resetPlayer(Player& player)
	{
		player.pos = { SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 };
	}

	void movePlayerUp(Player& player)
	{
		player.speed = player.jumpForce;
		player.animate = true;
		player.upwardsAngle = true;
	}

	void moveAngleUp(Player& player, float deltaTime)
	{
		if (player.upwardsAngle)
		{
			player.angle -= (player.gravityValue + fabsf(player.jumpForce)) * deltaTime;

			if (player.angle < -30)
				player.upwardsAngle = false;
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

				if (player.currentFrame > animationTotalFrames)
				{
					player.currentFrame = 0;
					player.animate = false;
				}

				player.frameRec.x = static_cast<float>(player.currentFrame) * (playerSheet.width / animationTotalFrames);
			}
		}
	}

	void movePlayerDown(Player& player, float deltaTime)
	{
		player.speed += player.gravityValue * deltaTime;

		player.pos.y += player.speed * deltaTime;

		if (player.speed > 0)
		{
			// El ángulo aumenta conforme la velocidad aumenta, hasta un máximo de 50
			player.angle = fminf(50, player.angle + (player.speed * 0.3f * deltaTime));
		}

	}

	void drawPlayer(Player player, Texture2D& windEffect, Texture2D& playerSprite)
	{
		if (player.animate)
		{
			Vector2 spriteRaltedPlayerPos = { player.pos.x + windEffect.width / 2, player.pos.y + windEffect.height / 2 };

			DrawTexturePro(
				windEffect,
				player.frameRec,
				Rectangle{ spriteRaltedPlayerPos.x - player.radius, spriteRaltedPlayerPos.y + player.radius, player.size, player.size },
				Vector2{ static_cast<float>(windEffect.width) / 2, static_cast<float>(windEffect.height) / 2 },
				0,
				WHITE);
		}

		Vector2 spriteRaltedPlayerPos = { player.pos.x, player.pos.y };
		player.frameRec = { 0,0, (float)playerSprite.width, (float)playerSprite.height };

		DrawTexturePro(
			playerSprite,
			player.frameRec,
			Rectangle{ player.pos.x, player.pos.y , player.size, player.size * 0.5f },
			Vector2{ player.radius, player.radius * 0.5f },
			player.angle,
			player.color);
	}
}