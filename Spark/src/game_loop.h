#ifndef GAME_LOOP_H
#define GAME_LOOP_H

namespace spark_luchelli
{

enum class GAME_STATES { NOT_STARTED, PAUSED, RUNNING, GAMEOVER, CREDITS };

struct GameStateMachine
{
	GAME_STATES currentState;
	GAME_STATES nextState;
};


void runGame();

void initializeGame();

void update();

void draw();

void close();

} //namespace spark_luchelli

#endif //GAME_LOOP_H