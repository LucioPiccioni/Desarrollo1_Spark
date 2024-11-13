#include "pause.h"

#include "game_data.h"
#include "gameplay.h"
#include "button.h"

namespace PAUSE
{
	const int buttonCount = 3;
	Vector2 mouse;
	BUTTON::Button buttons[buttonCount] = {};

	void initButtons()
	{
		float startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		float startY = SCREEN_HEIGHT - (BUTTON::buttonHeight * buttonCount + BUTTON::buttonSpacing * (buttonCount - 1));


		buttons[0].option = GAME_STATES::GAME_STATES::ONE_PLAYER_MODE;
		buttons[1].option = GAME_STATES::GAME_STATES::MAIN_MENU;
		buttons[2].option = GAME_STATES::GAME_STATES::WANT_TO_EXIT;

		buttons[0].text = "RESUME";
		buttons[1].text = "MENU";
		buttons[2].text = "EXIT";

		Color outline = BLACK;

		for (int i = 0; i < buttonCount; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
			buttons[i].outline = outline;
		}

	}

	void update(GAME_STATES::GAME_STATES& gameState)
	{
		mouse = GetMousePosition();

		for (int i = 0; i < buttonCount; i++)
		{
			if (BUTTON::isButtonClicked(mouse, buttons[i]))
			{
				buttons[i].color = WHITE;

				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					buttons[i].color = YELLOW;
				}

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					gameState = buttons[i].option;
				}
			}
		}

		if (gameState == GAME_STATES::GAME_STATES::MAIN_MENU)
			GAMEPLAY1P::initializeGame();
	}

	void draw(Font font)
	{
		Vector2 titlePos =
		{
			(SCREEN_WIDTH) / 2 - MeasureTextEx(font, "Pause", BUTTON::titlesFontSize, 2).x / 2,
			(SCREEN_HEIGHT) / 5
		};

		Color pastelPurple = { 214, 196, 224, 255 };


		DrawTextEx(font, "Pause", titlePos, BUTTON::titlesFontSize, 2, pastelPurple);

		for (int i = 0; i < buttonCount; i++)
		{
			BUTTON::drawButton(buttons[i], GetFontDefault());
		}
	}
}

