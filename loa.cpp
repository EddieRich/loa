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
	for (int i = 0; i < 6; i++)
	{
		chip[i].x = ((i + 1.5) * SQUARE_SIZE);
		chip[i].y = (0.5 * SQUARE_SIZE);
		chip[i].color = WHITE;
		chip[i + 6].x = ((i + 1.5) * SQUARE_SIZE);
		chip[i + 6].y = (7.5 * SQUARE_SIZE);
		chip[i + 6].color = WHITE;

		chip[i + 12].x = (0.5 * SQUARE_SIZE);
		chip[i + 12].y = ((i + 1.5) * SQUARE_SIZE);
		chip[i + 12].color = BLACK;
		chip[i + 18].x = (7.5 * SQUARE_SIZE);
		chip[i + 18].y = ((i + 1.5) * SQUARE_SIZE);
		chip[i + 18].color = BLACK;
	}
}

LinesOfAction::~LinesOfAction() {}

bool LinesOfAction::Update(float elapsed)
{
	return true;
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

	for (Chip& c : chip)
	{
		DrawCircleGradient(c.x, c.y, 50, c.color, Fade(c.color, 0.75));
		DrawCircleLines(c.x, c.y, 50, c.color);
	}
}
