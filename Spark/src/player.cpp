#include "player.h"
#include "raylib.h"

namespace Player
{

	void initializePlayer(Player& auxPlayer)
	{
		auxPlayer.gravityValue = 250;
		auxPlayer.speed = 0;
		auxPlayer.size = 30;
		auxPlayer.pos = { screenWidth / 5, screenHeight / 2 };
	}

	void resetPlayer(Player& auxPlayer)
	{
		auxPlayer.pos = { screenWidth / 5, screenHeight / 2 };
	}

	void movePlayerUp(Player& auxPlayer)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			auxPlayer.speed = auxPlayer.jumpForce;
			auxPlayer.animate = true;
		}
	}

	void movePlayerDown(Player& auxPlayer, float deltaTime)
	{
		auxPlayer.speed += auxPlayer.gravityValue * deltaTime;
		auxPlayer.pos.y += auxPlayer.speed * deltaTime;
	}

	void drawPlayer(Player& auxPlayer, Texture2D& playerSheet)
	{
		DrawTexturePro(
			playerSheet,
			auxPlayer.frameRec,
			Rectangle{ auxPlayer.pos.x - auxPlayer.size / 2, auxPlayer.pos.y - auxPlayer.size / 2, auxPlayer.size, auxPlayer.size },
			Vector2{ static_cast<float>(playerSheet.width) / 2, static_cast<float>(playerSheet.height) / 2 },
			0,
			WHITE);
	}

}