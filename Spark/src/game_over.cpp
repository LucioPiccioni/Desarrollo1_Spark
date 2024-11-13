#include "game_over.h"

#include "gameplay.h"

#include "button.h"
#include "game_data.h"

namespace GAME_OVER
{
	const int maxButtons = 3;
	Vector2 mouse;
	BUTTON::Button button[maxButtons] = {};

	void initButtons()
	{
		Color outline = BLACK;

		float startX = (static_cast<float>(SCREEN_WIDTH) - BUTTON::buttonWidth) / 2;
		float startY = ((static_cast<float>(SCREEN_HEIGHT) - SCREEN_HEIGHT / 5) - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1)));

		for (int i = 0; i < maxButtons; i++)
		{
			button[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
		}

		button[0].option = GAME_STATES::GAME_STATES::REPLAY;
		button[1].option = GAME_STATES::GAME_STATES::MAIN_MENU;
		button[2].option = GAME_STATES::GAME_STATES::EXIT;

		button[0].text = "REPLAY";
		button[1].text = "MENU";
		button[2].text = "EXIT";
	}

	void update(GAME_STATES::GAME_STATES& gameState)
	{
		mouse = GetMousePosition();

		for (int i = 0; i < maxButtons; i++)
		{
			if (BUTTON::isButtonClicked(mouse, button[i]))
			{
				button[i].color = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? YELLOW : WHITE;

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
					gameState = button[i].option;
			}
		}

		if (gameState == GAME_STATES::GAME_STATES::REPLAY)
		{
			gameState = GAME_STATES::GAME_STATES::PLAYING;
			GAMEPLAY::initializeGame();
		}
	}

	void draw(Font font)
	{
		Vector2 gameOverTextSize = MeasureTextEx(font, "GAME OVER", BUTTON::titlesFontSize, 0);
		Vector2 gameOverPos = { static_cast<float>(SCREEN_WIDTH) / 2 - gameOverTextSize.x / 2, static_cast<float>(SCREEN_HEIGHT) / 3 };

		DrawTextEx(font, "GAME OVER", gameOverPos, BUTTON::titlesFontSize, 0, RED);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(button[i], GetFontDefault());
		}
	}
}

