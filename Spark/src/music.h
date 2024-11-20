#pragma once
#include "raylib.h"

#include "state_machine.h"

namespace SOUND_TRACKS
{
	extern float volume;

	struct GameMusic
	{
		Music mainMenu = {};
		Music gameOver = {};
		Music gamePlay = {};
	};

	extern GameMusic music;

	void init();
	void unInit();

	void MusicControl(GAME_STATES::ProgramState& gameState);

	void MainMenuOrganization(Music*& actualMusic, Music* stopMusic[]);
	void GamePlayOrganization(Music*& actualMusic, Music* stopMusic[]);
	void GameOverOrganization(Music*& actualMusic, Music* stopMusic[]);
}