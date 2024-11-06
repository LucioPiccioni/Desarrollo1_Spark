
#ifndef  STATE_MACHINE_H
#define STATE_MACHINE_H

namespace spark_luchelli
{

enum class GAME_STATES { NOT_STARTED, PAUSED, RUNNING, GAMEOVER, CREDITS };

struct GameStateMachine
{
	GAME_STATES currentState;
	GAME_STATES nextState;
};

} //namespace spark_luchelli
#endif // STATE_MACHINE_H


