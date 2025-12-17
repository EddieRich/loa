#include <raylib.h>
#include "constants.h"
#include "chip.h"
#include "loa.h"

extern Vector2 game_mouse;
extern Camera2D camera;

const Color darkColor = (Color){ 112, 112, 112, 255 };
const Color lightColor = (Color){ 144, 144, 144, 255 };

LinesOfAction::LinesOfAction()
{
	state = &LinesOfAction::NewGame;
}

LinesOfAction::~LinesOfAction() {}

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
			DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, color);
			DrawRectangleLinesEx((Rectangle) { (float)(x * SQUARE_SIZE), (float)(y * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE }, 2.0 / camera.zoom, BLACK);
		}
	}

	for (const Chip& c : chip)
		c.Render();

	requires_render = false;
}

bool LinesOfAction::NewGame()
{
	for (Chip& c : chip)
		c.SetRandomOffScreen();

	for (int i = 0; i < 6; i++)
	{
		chip[i].color = WHITE;
		chip[i].MoveTo(((i + 1.5) * SQUARE_SIZE), (0.5 * SQUARE_SIZE));
		chip[i + 6].color = WHITE;
		chip[i + 6].MoveTo(((i + 1.5) * SQUARE_SIZE), (7.5 * SQUARE_SIZE));
		chip[i + 12].color = BLACK;
		chip[i + 12].MoveTo((0.5 * SQUARE_SIZE), ((i + 1.5) * SQUARE_SIZE));
		chip[i + 18].color = BLACK;
		chip[i + 18].MoveTo((7.5 * SQUARE_SIZE), ((i + 1.5) * SQUARE_SIZE));
	}

	state = &LinesOfAction::PlayerChooseChip;
	return true;
}

bool LinesOfAction::PlayerChooseChip()
{
	return false;
}

bool LinesOfAction::PlayerChooseTarget()
{
	return false;
}
