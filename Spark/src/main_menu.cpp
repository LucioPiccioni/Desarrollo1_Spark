#include "main_menu.h"
#include "button.h"
#include "game_data.h"

namespace MAIN_MENU
{
	static const int maxButtons = 5;
	static BUTTON::Button buttons[maxButtons];

	void initializeMenu(GAME_STATES::GAME_STATES& gameState)
	{
		initializeButtons();
		gameState = GAME_STATES::GAME_STATES::MENU;
	}

	void updateMenu(GAME_STATES::GAME_STATES& gameState)
	{
		Vector2 mouse = GetMousePosition();

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
					gameState = buttons[i].option;
			}
		}
	}

	void drawMenu()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], GetFontDefault());
		}
	}

	static void initializeButtons()
	{
		float startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		float startY = SCREEN_HEIGHT - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
		}

		buttons[0].option = GAME_STATES::GAME_STATES::Playing;
		buttons[1].option = GAME_STATES::GAME_STATES::Rules;
		buttons[2].option = GAME_STATES::GAME_STATES::Credits;
		buttons[3].option = GAME_STATES::GAME_STATES::WantToExit;

		Color outline = BLACK;
	}

}

