#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "chip.h"

Texture2D Chip::texChip;

Chip::Chip()
{
	SetRandomOffScreen();
	selected = false;
}

void Chip::SetRandomOffScreen()
{
	int sw = GetScreenWidth();
	int sh = GetScreenHeight();
	int r = GetRandomValue(0, 1000000);
	if (r < 250000)
	{
		py = fy = ty = -CHIP_RADIUS;
		px = fx = tx = GetRandomValue(-CHIP_RADIUS, sw + CHIP_RADIUS);
	}
	else if (r < 500000)
	{
		px = fx = tx = sw + CHIP_RADIUS;
		py = fy = ty = GetRandomValue(-CHIP_RADIUS, sh + CHIP_RADIUS);
	}
	else if (r < 750000)
	{
		py = fy = ty = sh + CHIP_RADIUS;
		px = fx = tx = GetRandomValue(-CHIP_RADIUS, sw + CHIP_RADIUS);
	}
	else
	{
		px = fx = tx = -CHIP_RADIUS;
		py = fy = ty = GetRandomValue(-CHIP_RADIUS, sh + CHIP_RADIUS);
	}

	t = 1.0;
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
