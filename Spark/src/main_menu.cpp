#include "main_menu.h"
#include "button.h"
#include "game_data.h"

namespace MAIN_MENU
{
	static const int maxButtons = 5;
	static BUTTON::Button buttons[maxButtons];
	Texture2D gamesTitle;

	void initializeMenu()
	{
		initializeButtons();
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
			else
			{
				buttons[i].color = { 255, 182, 193, 255 };
			}
		}
	}

	void drawMenu()
	{
		DrawText("v0.3", 0, 0, 20, WHITE);

		DrawTexturePro(
			gamesTitle,
			Rectangle{ 0, 0, static_cast<float>(gamesTitle.width), static_cast<float>(gamesTitle.height) },  // Fuente: toda la imagen original
			Rectangle{ static_cast<float>(SCREEN_WIDTH) / 2 - gamesTitle.width / 2,  // Posición X centrada
					   static_cast<float>(SCREEN_HEIGHT) / 3 - gamesTitle.height / 2,  // Posición Y centrada
					   static_cast<float>(gamesTitle.width),  // Ancho del título
					   static_cast<float>(gamesTitle.height) },  // Altura del título
			Vector2{ 0, 0 },  // Offset del centro
			0.0f,  // Sin rotación
			WHITE  // Sin tintes de color
		);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], GetFontDefault());
		}

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], GetFontDefault());
		}
	}

	void initializeButtons()
	{
		float startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		float startY = SCREEN_HEIGHT - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
		}

		buttons[0].option = GAME_STATES::GAME_STATES::ONE_PLAYER_MODE;
		buttons[1].option = GAME_STATES::GAME_STATES::TWO_PLAYER_MODE;
		buttons[2].option = GAME_STATES::GAME_STATES::MAIN_MENU;
		buttons[3].option = GAME_STATES::GAME_STATES::MAIN_MENU;
		buttons[4].option = GAME_STATES::GAME_STATES::EXIT;

		buttons[0].text = "1P MODE";
		buttons[1].text = "2P MODE";
		buttons[2].text = "RULES";
		buttons[3].text = "CREDITS";
		buttons[4].text = "EXIT";

		Color outline = BLACK;
	}

}

