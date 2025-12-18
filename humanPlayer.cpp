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

	ploa->target = 0ULL;
	ploa->requires_render = true;

	// is the mouse over a chip
	ci = -1;
	for (i = 23; i >= 0 && ci < 0; i--)
	{
		if (ploa->chip[i].Contains(game_mouse))
			ci = i;
	}

	if (ci >= 0 && isWhite ? (ci < 12) : (ci >= 12))
	{
		ploa->SetTargetsFor(ci);
		if (ploa->target != 0ULL)
		{
			ploa->chip[ci].selected = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				return true;
		}
	}

	return false;
}

bool HumanPlayer::ChooseTarget(LinesOfAction* ploa)
{
	return false;
}
