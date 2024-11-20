#include "raylib.h"

#include "state_machine.h"
#include "game_data.h"

namespace CONFIRM_EXIT
{
	void initButtons();

	void update(GAME_STATES::ProgramState& gameState);

	void draw(Font font);
}