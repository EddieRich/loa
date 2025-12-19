#include <raylib.h>
#include <raymath.h>
#include "constants.h"
#include "chip.h"
#include "player.h"
#include "humanPlayer.h"
#include "loa.h"

bool showTitleScreen = false;
bool quit_requested = false;

const char* title = "Lines Of Actiion";

int winx, winy, winw, winh;
Vector2 screen_mouse;
Vector2 game_mouse;
Camera2D camera;

void set_scale()
{
	float sw = (float)GetScreenWidth();
	float sh = (float)GetScreenHeight();
	camera.zoom = std::min(sw / GAME_SIZE, sh / GAME_SIZE);
	camera.offset.x = (sw - (GAME_SIZE * camera.zoom)) * 0.5f;
	camera.offset.y = (sh - (GAME_SIZE * camera.zoom)) * 0.5f;
	camera.target.x = 0;
	camera.target.y = 0;
}

void events(LinesOfAction* ploa)
{
	if (IsKeyPressed(KEY_F11))	// pressed and released
	{
		if (IsWindowFullscreen())
		{
			ToggleFullscreen();
			SetWindowSize(winw, winh);
			SetWindowPosition(winx, winy);
		}
		else
		{
			Vector2 pos = GetWindowPosition();
			winx = (int)pos.x;
			winy = (int)pos.y;
			winw = GetScreenWidth();
			winh = GetScreenHeight();
			int monitor = GetCurrentMonitor();
			SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
			ToggleFullscreen();
		}
	}

	if (IsKeyPressed(KEY_Q))
	{
		if (showTitleScreen)
			quit_requested = true;
		else
			showTitleScreen = true;
	}

	if (IsWindowResized())
	{
		set_scale();
		ploa->requires_render = true;
	}

	screen_mouse = GetMousePosition();
	game_mouse = Vector2Scale(Vector2Subtract(screen_mouse, camera.offset), 1.0 / camera.zoom);
}

int main(void)
{
	SetTraceLogLevel(LOG_NONE);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(800, 600, title);
	SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	set_scale();
	SetTargetFPS(30);

	LinesOfAction loa;
	loa.requires_render = true;

	while (!WindowShouldClose() && !quit_requested)
	{
		events(&loa);

		BeginDrawing();
		if (showTitleScreen)
			//render_title_screen(&lindy);
			ClearBackground(BLACK);
		else
		{
			if (loa.Update(GetFrameTime()))
			{
				BeginMode2D(camera);
				loa.Render();
				EndMode2D();
			}
		}
		EndDrawing();
	}

	loa.Shutdown();

	CloseWindow();        // Close window and OpenGL context
	return 0;
}
