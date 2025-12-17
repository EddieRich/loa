#include <raylib.h>
#include "constants.h"
#include "chip.h"
#include "player.h"
#include "humanPlayer.h"
#include "loa.h"

extern Vector2 game_mouse;
//extern Camera2D camera;

HumanPlayer::HumanPlayer(bool white) : Player(white)
{}

bool HumanPlayer::ChooseChip(LinesOfAction* ploa)
{
	int i, ci;
	for (i = 0; i < 24; i++)
		ploa->chip[i].selected = false;

	// is the mouse over a chip
	ci = -1;
	for (i = 23; i >= 0 && ci < 0; i--)
	{
		if (ploa->chip[i].Contains(game_mouse))
			ci = i;
	}

	if (ci >= 0 && ColorIsEqual(ploa->chip[ci].color, isWhite ? WHITE : BLACK))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			// actually select it
		}
		else
		{
			ploa->chip[ci].selected = true;
		}
	}

	return true;
}

bool HumanPlayer::ChooseTarget()
{
	return false;
}
