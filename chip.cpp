#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "chip.h"

extern Camera2D camera;
Texture2D Chip::texChip;

Chip::Chip()
{
	SetRandomOffScreen();
	selected = false;
}

void Chip::SetRandomOffScreen(bool move_to)
{
	int nx, ny;

	int m = GetCurrentMonitor();
	int w = GetMonitorWidth(m);
	int h = GetMonitorHeight(m);
	int chip_dia = CHIP_RADIUS * 2;

	Vector2 min = GetScreenToWorld2D((Vector2) { (float)-chip_dia, (float)-chip_dia }, camera);
	Vector2 max = GetScreenToWorld2D((Vector2) { (float)(w + chip_dia), (float)(h + chip_dia) }, camera);

	bx = by = -1;

	int r = GetRandomValue(0, 1000000);
	if (r < 250000)
	{
		ny = min.y;
		nx = GetRandomValue(min.x, max.x);
	}
	else if (r < 500000)
	{
		nx = max.x;
		ny = GetRandomValue(min.y, max.y);
	}
	else if (r < 750000)
	{
		ny = max.y;
		nx = GetRandomValue(min.x, min.y);
	}
	else
	{
		nx = min.x;
		ny = GetRandomValue(min.y, max.y);
	}

	if (move_to)
		MoveTo(nx, ny);
	else
	{
		px = fx = tx = nx;
		py = fy = ty = ny;
		t = 1.0;
	}
}

bool Chip::Update(float elapsed)
{
	if (t < 1.0)
	{
		t += elapsed;
		if (t > 1.0)
		{
			t = 1.0;
			px = tx;
			py = ty;
		}
		else
		{
			px = fx + (tx - fx) * t;
			py = fy + (ty - fy) * t;
		}

		return true;
	}

	return false;
}

void Chip::Render() const
{
	DrawTexture(texChip, px - CHIP_RADIUS, py - CHIP_RADIUS, selected ? DARKGREEN : color);
}

bool Chip::Contains(Vector2 pt)
{
	return Vector2Distance((Vector2) { (float)px, (float)py }, pt) < CHIP_RADIUS;
}

void Chip::MoveTo(int nx, int ny)
{
	fx = px;
	fy = py;
	tx = nx;
	ty = ny;
	t = 0.0;
}
