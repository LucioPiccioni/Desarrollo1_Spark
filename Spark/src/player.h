#pragma once

namespace Player
{

	struct Player
	{
		Vector2 pos;

		Rectangle frameRec;

		int currentFrame = 0;
		float framesCounter = 0;

		float jumpForce;
		float gravityValue;

		float size;
		float radius;
		float speed;

		bool animate = false;
		bool collide = false;
	};

	void initializePlayer(Player& player);

	void resetPlayer(Player& player);

	void movePlayerUp(Player& player);

	void movePlayerDown(Player& player, float deltaTime);

	void drawPlayer(Player& player, Texture2D& playerSheet);
}