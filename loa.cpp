#include <raylib.h>
#include "constants.h"
#include "chip.h"
#include "player.h"
#include "humanPlayer.h"
#include "loa.h"

Color darkColor = (Color){ 112, 112, 112, 255 };
Color lightColor = (Color){ 144, 144, 144, 255 };
Color darkChip = (Color){ 16, 16, 16, 255 };
Color lightChip = (Color){ 240, 240, 240, 255 };

LinesOfAction::LinesOfAction()
{
	state = &LinesOfAction::NewGame;
	player[0] = 0;
	player[1] = 0;
	pi = 0;
	Image img = GenImageGradientSquare(SQUARE_SIZE, SQUARE_SIZE, 0.95, WHITE, BLACK);
	texSquare = LoadTextureFromImage(img);
	UnloadImage(img);
	img = GenImageGradientRadial(CHIP_RADIUS * 2, CHIP_RADIUS * 2, 0.95, WHITE, Fade(BLACK, 0.0f));
	Chip::texChip = LoadTextureFromImage(img);
	UnloadImage(img);
}

LinesOfAction::~LinesOfAction()
{}

void LinesOfAction::Shutdown()
{
	UnloadTexture(texSquare);
	UnloadTexture(Chip::texChip);
	ClearPlayers();
}

bool LinesOfAction::ChipAt(int bx, int by)
{
	for (int i = 0; i < 24; i++)
	{
		if (chip[i].bx == bx && chip[i].by == by)
			return true;
	}

	return false;
}

int LinesOfAction::ChipIndexAt(int bx, int by)
{
	for (int i = 0; i < 24; i++)
	{
		if (chip[i].bx == bx && chip[i].by == by)
			return i;
	}

	return -1;
}

int LinesOfAction::SelectedChipIndex()
{
	for (int i = 0; i < 24; i++)
	{
		if (chip[i].selected)
			return i;
	}

	return -1;
}

bool LinesOfAction::LegalMove(int ci, int dx, int dy, int count)
{
	if (count == 0)
		return false;

	int bx = chip[ci].bx;
	int by = chip[ci].by;
	int ii;
	// check in between squares for opponent chips
	for (int i = 0; i < (count - 1); i++)
	{
		bx += dx;
		by += dy;
		if (bx >= 0 && bx <= 7 && by >= 0 && by <= 7)
		{
			ii = ChipIndexAt(bx, by);
			// if there is a chip and it's the opponent color
			if (ii >= 0 && ((ci < 12) ? (ii > 11) : (ii < 12)))
				return false;
		}
		else
			return false;
	}
	// check the target square
	bx += dx;
	by += dy;
	if (bx >= 0 && bx <= 7 && by >= 0 && by <= 7)
	{
		ii = ChipIndexAt(bx, by);
		// if there is a chip and it's the players color
		if (ii >= 0 && ((ci < 12) ? (ii < 12) : (ii > 11)))
			return false;
	}
	else
		return false;

	return true;
}

int LinesOfAction::GetLineCount(int x, int y, int dx, int dy)
{
	int cc = 0;		// chip count

	// first check the "line of action" in the dx dy direction
	int bx = x;
	int by = y;
	while (bx >= 0 && bx <= 7 && by >= 0 && by <= 7)
	{
		if (ChipAt(bx, by))
			cc++;

		bx += dx;
		by += dy;
	}

	// now check the opposite dx dy on the same "line of action"
	bx = x - dx;
	by = y - dy;
	while (bx >= 0 && bx <= 7 && by >= 0 && by <= 7)
	{
		if (ChipAt(bx, by))
			cc++;

		bx -= dx;
		by -= dy;
	}

	return cc;
}

void LinesOfAction::SetTargetsFor(int chip_index)
{
	target = 0ULL;

	// horizontal
	int chip_count = GetLineCount(chip[chip_index].bx, chip[chip_index].by, 1, 0);
	if (LegalMove(chip_index, 1, 0, chip_count))
		SetTargetFlag(chip[chip_index].bx + chip_count, chip[chip_index].by);
	if (LegalMove(chip_index, -1, 0, chip_count))
		SetTargetFlag(chip[chip_index].bx - chip_count, chip[chip_index].by);

	// vertical
	chip_count = GetLineCount(chip[chip_index].bx, chip[chip_index].by, 0, 1);
	if (LegalMove(chip_index, 0, 1, chip_count))
		SetTargetFlag(chip[chip_index].bx, chip[chip_index].by + chip_count);
	if (LegalMove(chip_index, 0, -1, chip_count))
		SetTargetFlag(chip[chip_index].bx, chip[chip_index].by - chip_count);

	// diagonal 1 '\'
	chip_count = GetLineCount(chip[chip_index].bx, chip[chip_index].by, 1, 1);
	if (LegalMove(chip_index, 1, 1, chip_count))
		SetTargetFlag(chip[chip_index].bx + chip_count, chip[chip_index].by + chip_count);
	if (LegalMove(chip_index, -1, -1, chip_count))
		SetTargetFlag(chip[chip_index].bx - chip_count, chip[chip_index].by - chip_count);

	// diagonal 2 '/'
	chip_count = GetLineCount(chip[chip_index].bx, chip[chip_index].by, -1, 1);
	if (LegalMove(chip_index, -1, 1, chip_count))
		SetTargetFlag(chip[chip_index].bx - chip_count, chip[chip_index].by + chip_count);
	if (LegalMove(chip_index, 1, -1, chip_count))
		SetTargetFlag(chip[chip_index].bx + chip_count, chip[chip_index].by - chip_count);
}

void LinesOfAction::SetTargetFlag(int bx, int by)
{
	unsigned long long int mask = 1ULL << (by * 8 + bx);
	target |= mask;
}

bool LinesOfAction::IsTarget(int bx, int by)
{
	unsigned long long int mask = 1ULL << (by * 8 + bx);
	return ((target & mask) != 0ULL);
}

void LinesOfAction::ClearPlayers()
{
	if (player[0])
	{
		delete player[0];
		player[0] = 0;
	}

	if (player[1])
	{
		delete player[1];
		player[1] = 0;
	}
}

bool LinesOfAction::Update(float elapsed)
{
	for (Chip& c : chip)
		requires_render |= c.Update(elapsed);

	if (requires_render)
		return true;

	return (this->*state)();
}

void LinesOfAction::Render()
{
	ClearBackground((Color) { 48, 8, 32, 255 });
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Color color = ((x ^ y) & 1) ? darkColor : lightColor;
			DrawTexture(texSquare, x * SQUARE_SIZE, y * SQUARE_SIZE, color);
		}
	}

	for (const Chip& c : chip)
		c.Render();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (IsTarget(x, y))
				DrawCircle((x + 0.5f) * SQUARE_SIZE, (y + 0.5f) * SQUARE_SIZE, CHIP_RADIUS / 2, GOLD);
		}
	}

	requires_render = false;
}

bool LinesOfAction::NewGame()
{
	ClearPlayers();
	player[0] = new HumanPlayer(false);
	player[1] = new HumanPlayer(true);
	pi = 0;
	target = 0ULL;

	for (Chip& c : chip)
		c.SetRandomOffScreen();

	for (int i = 0; i < 6; i++)
	{
		chip[i].color = darkChip;
		chip[i].bx = i + 1;
		chip[i].by = 0;
		chip[i].MoveTo(((i + 1.5) * SQUARE_SIZE), (0.5 * SQUARE_SIZE));
		chip[i + 6].color = darkChip;
		chip[i + 6].bx = i + 1;
		chip[i + 6].by = 7;
		chip[i + 6].MoveTo(((i + 1.5) * SQUARE_SIZE), (7.5 * SQUARE_SIZE));
		chip[i + 12].color = lightChip;
		chip[i + 12].bx = 0;
		chip[i + 12].by = i + 1;
		chip[i + 12].MoveTo((0.5 * SQUARE_SIZE), ((i + 1.5) * SQUARE_SIZE));
		chip[i + 18].color = lightChip;
		chip[i + 18].bx = 7;
		chip[i + 18].by = i + 1;
		chip[i + 18].MoveTo((7.5 * SQUARE_SIZE), ((i + 1.5) * SQUARE_SIZE));
	}

	state = &LinesOfAction::PlayerChooseChip;
	return true;
}

bool LinesOfAction::PlayerChooseChip()
{
	if (player[pi]->ChooseChip(this))
		state = &LinesOfAction::PlayerChooseTarget;

	return true;
}

bool LinesOfAction::PlayerChooseTarget()
{
	int result = player[pi]->ChooseTarget(this);
	if (result == -1)
		state = &LinesOfAction::PlayerChooseChip;
	else if (result == 1)
		state = &LinesOfAction::CheckPlayerWins;

	return true;
}

bool LinesOfAction::CheckPlayerWins()
{
	// assume no for now
	pi = pi ^ 1;
	state = &LinesOfAction::PlayerChooseChip;
	return true;
}
