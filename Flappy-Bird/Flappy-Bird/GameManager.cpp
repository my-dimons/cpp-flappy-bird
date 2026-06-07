#include "GameManager.h"
#include "GameConstants.h"
#include "raylib.h"
#include "Pipes.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

GameConstants* gameConstants = new GameConstants();

Bird bird = { 0 };
std::vector<Pipe*> pipes;

const float circleRadius = 32.0f;

void GameManager::CloseGame() {
	CloseWindow();
}

void GameManager::InitGame() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameConstants->windowName);
	SetTargetFPS(FPS);

	pipes = GeneratePipes(1);
	//std::cout << pipes->size();

	bird.position = { BIRD_X_POS, 0 };
}

void GameManager::GameLoop() {
	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		UpdatePlayer(&bird, deltaTime);
		UpdateEnv(&pipes, deltaTime);
		// Circle movement
		//if (IsKeyDown(KEY_RIGHT)) circle.x += 2.0f;
		//if (IsKeyDown(KEY_LEFT)) circle.x -= 2.0f;
		//if (IsKeyDown(KEY_UP)) circle.y -= 2.0f;
		//if (IsKeyDown(KEY_DOWN)) circle.y += 2.0f;

		// camera rotation
		//if (IsKeyDown(KEY_Q)) camera.rotation--;
		//if (IsKeyDown(KEY_E)) camera.rotation++;

		BeginDrawing();
		RenderFrame();
		EndDrawing();
	}
}

void GameManager::RenderFrame() {
	ClearBackground(RAYWHITE);

	RenderObjects();

	RenderText();
}

void GameManager::RenderObjects() {
	DrawCircleV(bird.position, circleRadius, GREEN);

	for (Pipe* pipe : pipes) {
		DrawRectangle(30, 30, 30, 30, GREEN);
		std::cout << pipe->rect.y << std::endl;
		DrawRectangle(pipe->rect.x, pipe->rect.y, pipe->rect.width, pipe->rect.height, pipe->color);
	}
	//DrawLine(0, -SCREEN_HEIGHT * 10, 0, SCREEN_HEIGHT * 10, RED); // vertical line
	//DrawLine(-SCREEN_WIDTH * 10, 0, SCREEN_WIDTH * 10, 0, RED); // horizontal line
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

void GameManager::UpdatePlayer(Bird* bird, float deltaTime) {
	if (IsKeyDown(KEY_SPACE)) {
		bird->speed = -BIRD_JUMP_SPEED;
	}

	// Update Position
	bird->position.y += bird->speed * deltaTime;

	if (bird->position.y > SCREEN_HEIGHT) {
		bird->position.y = SCREEN_HEIGHT;
	} else if (bird->position.y < 0) {
		bird->position.y = 0;
		bird->speed = 0;
	}

	bird->speed += GRAVITY * deltaTime;
}

void GameManager::UpdateEnv(std::vector<Pipe*>* pipes, float deltaTime) {
	for (Pipe* pipe : *pipes) {
		pipe->rect.x -= (SCROLLING_SPEED * deltaTime);
		//std::cout << pipe->rect.x << std::endl;
	}
}