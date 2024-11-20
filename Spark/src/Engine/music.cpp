#include "music.h"

namespace SOUND_TRACKS
{

	float volume = 0.5;

	GameMusic music = {};

	void init()
	{
		music.mainMenu = LoadMusicStream("res/music/Louie's Lullaby - Harris Cole.mp3");
		music.gamePlay = LoadMusicStream("res/music/Breathtaking - Purrple Cat.mp3");
		music.gameOver = LoadMusicStream("res/music/JEN - QUIET NIGHTS - soulmate.mp3");
	}

	void unInit()
	{
		UnloadMusicStream(music.mainMenu);
		UnloadMusicStream(music.gamePlay);
		UnloadMusicStream(music.gameOver);
	}

	void MusicControl(GAME_STATES::ProgramState& programState)
	{
		const int AllMusic = 2;

		Music* actualMusic = nullptr;
		Music* stopMusic[AllMusic] = { nullptr };

		switch (programState.actual)
		{
		case GAME_STATES::Gamestate::MAIN_MENU:

			MainMenuOrganization(actualMusic, stopMusic);
			break;

		case GAME_STATES::Gamestate::ONE_PLAYER_MODE:
		case GAME_STATES::Gamestate::TWO_PLAYER_MODE:

			GamePlayOrganization(actualMusic, stopMusic);
			break;

		case GAME_STATES::Gamestate::GAME_OVER:

			GameOverOrganization(actualMusic, stopMusic);
			break;

		case GAME_STATES::Gamestate::RULES:

			MainMenuOrganization(actualMusic, stopMusic);
			break;

		case GAME_STATES::Gamestate::CREDITS:

			MainMenuOrganization(actualMusic, stopMusic);
			break;

		case GAME_STATES::Gamestate::WANT_TO_EXIT:

			if (programState.previusHud == GAME_STATES::Gamestate::MAIN_MENU)
				MainMenuOrganization(actualMusic, stopMusic);
			else if (programState.previusHud == GAME_STATES::Gamestate::GAME_OVER)
				GameOverOrganization(actualMusic, stopMusic);
			else
				GamePlayOrganization(actualMusic, stopMusic);

			break;

		case GAME_STATES::Gamestate::EXIT:
			break;

		default:
			break;
		}

		for (int i = 0; i < AllMusic; i++)
		{
			if (stopMusic[i] != nullptr)
			{
				if (IsMusicStreamPlaying(*stopMusic[i]))
					StopMusicStream(*stopMusic[i]);
			}
		}

		if (actualMusic != nullptr)
		{
			SetMusicVolume(*actualMusic, volume);

			if (!IsMusicStreamPlaying(*actualMusic))
				PlayMusicStream(*actualMusic);

			UpdateMusicStream(*actualMusic);
		}
	}

	void MainMenuOrganization(Music*& actualMusic, Music* stopMusic[])
	{
		actualMusic = &music.mainMenu;

		stopMusic[0] = &music.gamePlay;
		stopMusic[1] = &music.gameOver;
	}

	void GamePlayOrganization(Music*& actualMusic, Music* stopMusic[])
	{
		actualMusic = &music.gamePlay;

		stopMusic[0] = &music.mainMenu;
		stopMusic[1] = &music.gameOver;
	}

	void GameOverOrganization(Music*& actualMusic, Music* stopMusic[])
	{
		actualMusic = &music.gameOver;

		stopMusic[0] = &music.mainMenu;
		stopMusic[1] = &music.gamePlay;
	}
}