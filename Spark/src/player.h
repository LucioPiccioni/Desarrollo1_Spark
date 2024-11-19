#pragma once

#include "raylib.h"

namespace PLAYER
{
	struct Player
	{
		Vector2 pos = {};

		Rectangle frameRec = {};

		int currentFrame = 0;
		float framesCounter = 0.0f;

		float jumpForce = 0.0f;
		float gravityValue = -300;

		int points = 0;

		float size = 0.0f;
		float radius = 0.0f;
		float angle = 0.0f;

		float speed = 0.0f;

		bool animate = false;
	};

	void initializePlayer(Player& player, Texture2D& playerSheet);

	void resetPlayer(Player& player);

	void movePlayerUp(Player& player);

	void Anitmation(Player& player, Texture2D& playerSheet, float deltaTime);

	void movePlayerDown(Player& player, float deltaTime);

	void drawPlayer(Player player, Texture2D& playerSheet, Texture2D& playerSprite);
}