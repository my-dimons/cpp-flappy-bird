#include "GameManager.h"
#include "GameConstants.h"
#include "raylib.h"
#include <math.h>
#include <iostream>

GameConstants* gameConstants = new GameConstants();

Camera2D camera = { 0 };

Vector2 circle = { 0, 0 };

const float circleRadius = 32.0f;

void GameManager::CloseGame() {
	CloseWindow();
}

void GameManager::InitGame() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameConstants->windowName);
	SetTargetFPS(FPS);

	camera.target = circle;
	camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}


void GameManager::GameLoop() {
	while (!WindowShouldClose()) {

		camera.target = circle;

		// Circle movement
		if (IsKeyDown(KEY_RIGHT)) circle.x += 2.0f;
		if (IsKeyDown(KEY_LEFT)) circle.x -= 2.0f;
		if (IsKeyDown(KEY_UP)) circle.y -= 2.0f;
		if (IsKeyDown(KEY_DOWN)) circle.y += 2.0f;

		// camera rotation
		if (IsKeyDown(KEY_Q)) camera.rotation--;
		if (IsKeyDown(KEY_E)) camera.rotation++;

		BeginDrawing();
		RenderFrame();
		EndDrawing();
	}
}

void GameManager::RenderFrame() {
	ClearBackground(RAYWHITE);

	RenderMode2D();

	RenderText();
}

void GameManager::RenderMode2D() {
	BeginMode2D(camera);

	DrawCircleV(circle, circleRadius, GREEN);

	DrawLine(0, -SCREEN_HEIGHT * 10, 0, SCREEN_HEIGHT * 10, RED); // vertical line
	DrawLine(-SCREEN_WIDTH * 10, 0, SCREEN_WIDTH * 10, 0, RED); // horizontal line

	EndMode2D();
}

void GameManager::RenderText() {
	if (DRAW_DEBUG_TEXT)
		RenderDebugText();

	DrawText("Move the ball with the arrow keys!", 10, 30, 20, DARKGRAY);
	DrawText("Click 'Esc' to quit", 10, 50, 20, DARKGRAY);
}

void GameManager::RenderDebugText() {
	// FPS Text
	const char* fpsText = TextFormat("FPS: %i/%i (%02.02f ms)", GetFPS(), FPS, GetFrameTime());
	DrawText(fpsText, 10, 10, 20, DARKGREEN);
}