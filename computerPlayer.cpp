#include <raylib.h>
#include "constants.h"
#include "chip.h"
#include "player.h"
#include "computerPlayer.h"
#include "loa.h"

extern Vector2 game_mouse;

ComputerPlayer::ComputerPlayer(bool black) : Player(black)
{}

// ------------------------------------------------
//   ComputerPlayer needs it's own state machine
// ------------------------------------------------
bool ComputerPlayer::ChooseChip(LinesOfAction* ploa)
{
	for (int i = 0, ci = isBlack ? 0 : 12; i < 12; i++, ci++)
	{
		if (ploa->chip[ci].bx < 0 || ploa->chip[ci].by < 0)
			continue;
	}

	return false;
}

int ComputerPlayer::ChooseTarget(LinesOfAction* ploa)
{
	return 0;
}

