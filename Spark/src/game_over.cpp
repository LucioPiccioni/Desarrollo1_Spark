#include "game_over.h"

#include "gameplay.h"
#include "gameplay2p.h"

#include "button.h"
#include "game_data.h"

namespace GAME_OVER
{
	const int maxButtons = 3;
	Vector2 mouse;
	BUTTON::Button buttons[maxButtons] = {};

	void initButtons()
	{
		float startX = (static_cast<float>(SCREEN_WIDTH) - BUTTON::buttonWidth) / 2;
		float startY = ((static_cast<float>(SCREEN_HEIGHT) - SCREEN_HEIGHT / 5) - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1)));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
		}

		buttons[0].option = GAME_STATES::Gamestate::REPLAY;
		buttons[1].option = GAME_STATES::Gamestate::MAIN_MENU;
		buttons[2].option = GAME_STATES::Gamestate::EXIT;

		buttons[0].text = "REPLAY";
		buttons[1].text = "MENU";
		buttons[2].text = "EXIT";
	}

	void update(GAME_STATES::ProgramState& gameState)
	{
		mouse = GetMousePosition();

		for (int i = 0; i < maxButtons; i++)
		{
			if (BUTTON::isButtonClicked(mouse, buttons[i]))
			{
				buttons[i].color = WHITE;

				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					buttons[i].color = YELLOW;
				}

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
					gameState.actual = buttons[i].option;
			}
			else
			{
				buttons[i].color = { 255, 182, 193, 255 };
			}
		}

		if (gameState.actual == GAME_STATES::Gamestate::REPLAY)
		{
			if (gameState.previus == GAME_STATES::Gamestate::ONE_PLAYER_MODE)
				GAMEPLAY_1P::initializeGame();
			else
				GAMEPLAY_2P::initializeGame();

			gameState.actual = gameState.previus;
		}
	}

	void draw(Font font)
	{
		Vector2 gameOverTextSize = MeasureTextEx(font, "GAME OVER", BUTTON::titlesFontSize, 0);
		Vector2 gameOverPos = { static_cast<float>(SCREEN_WIDTH) / 2 - gameOverTextSize.x / 2, static_cast<float>(SCREEN_HEIGHT) / 3 };

		DrawTextEx(font, "GAME OVER", gameOverPos, BUTTON::titlesFontSize, 0, RED);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], GetFontDefault());
		}
	}
}

