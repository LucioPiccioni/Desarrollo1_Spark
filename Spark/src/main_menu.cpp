#include "main_menu.h"

#include "sounds.h"
#include "button.h"
#include "game_data.h"
#include "sprites.h"

namespace MAIN_MENU
{
	static const int maxButtons = 5;
	static BUTTON::Button buttons[maxButtons];
	Texture2D gamesTitle;

	void initializeMenu()
	{
		SPRITES::spritesMovement = { 0,0,0,0 };
		initializeButtons();
	}

	void updateMenu(GAME_STATES::ProgramState& gameState)
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
				{
					StopSound(SOUNDS::gameSounds.button);
					PlaySound(SOUNDS::gameSounds.button);
					gameState.actual = buttons[i].option;
				}
			}
			else
			{
				buttons[i].color = { 255, 182, 193, 255 };
			}
		}

		SPRITES::updateTexturesPos(GetFrameTime());
	}

	void drawMenu(Font font)
	{
		SPRITES::drawBackgroundAssets();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 125 });

		DrawText("v0.4", 0, 0, 20, WHITE);

		DrawTextPro(font, 
			"The Spark", 
			Vector2{ (SCREEN_WIDTH - MeasureTextEx(font, "The Spark", BUTTON::titlesFontSize, 0).x) * 0.5f, 
					 MeasureTextEx(font, "The Spark", BUTTON::titlesFontSize, 0).y * 0.5f },
			Vector2{0, 0},
			0, BUTTON::titlesFontSize,
			0, 
			YELLOW);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}
	}

	void initializeButtons()
	{
		float startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		float startY = SCREEN_HEIGHT - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
			buttons[i].color = BLACK;
		}

		buttons[0].option = GAME_STATES::Gamestate::ONE_PLAYER_MODE;
		buttons[1].option = GAME_STATES::Gamestate::TWO_PLAYER_MODE;
		buttons[2].option = GAME_STATES::Gamestate::MAIN_MENU;
		buttons[3].option = GAME_STATES::Gamestate::CREDITS;
		buttons[4].option = GAME_STATES::Gamestate::WANT_TO_EXIT;

		buttons[0].text = "Solo MODE";
		buttons[1].text = "Coop MODE";
		buttons[2].text = "RULES";
		buttons[3].text = "CREDITS";
		buttons[4].text = "EXIT";

	}

}

