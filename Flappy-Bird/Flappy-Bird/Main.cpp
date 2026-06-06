#include "raylib.h"
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 450;

void InitGame() {
	InitWindow(screenWidth, screenHeight, "Flappy Bird");
	SetTargetFPS(60);
}

void RenderFrame() {
	ClearBackground(RAYWHITE);
	DrawText("Text!", 190, 200, 20, BLACK);
}

void GameLoop() {
	while (!WindowShouldClose()) {
		BeginDrawing();

		RenderFrame();

		EndDrawing();
	}
}

int main() {
	InitGame();

	GameLoop();

	CloseWindow();

	return 0;
}