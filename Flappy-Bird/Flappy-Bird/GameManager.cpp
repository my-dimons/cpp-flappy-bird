#include "GameManager.h"
#include "GameConstants.h"
#include "raylib.h"
#include "Pipes.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

GameConstants gameConstants;

Bird bird = { 0 };
std::vector<Pipe> pipes;

const float circleRadius = 58;
bool collision = false;

void GameManager::CloseGame() {
	CloseWindow();
}

void GameManager::InitGame() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameConstants.windowName);
	SetTargetFPS(FPS);

	pipes = GeneratePipes(200);
	std::cout << pipes.size();
	bird.position = { BIRD_X_POS, 0 };
}

void GameManager::GameLoop() {
	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		UpdatePlayer(&bird, deltaTime);
		UpdateEnv(&pipes, deltaTime);

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

	//std::cout << pipes[0]->rect.x << std::endl;
	for (Pipe pipe : pipes) {
		//DrawRectangle(30, 30, 30, 30, GREEN);
		//std::cout << pipe->rect.x << std::endl;
		DrawRectangle(pipe.rect.x, pipe.rect.y, pipe.rect.width, pipe.rect.height, pipe.color);
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
	if (IsKeyPressed(KEY_SPACE)) {
		bird->speed = -BIRD_JUMP_SPEED;
	}

	// Collision detection
	for (int i = 0; i < pipes.size(); i++) {
		Pipe* o = &pipes[i];
		Vector2* p = &(bird->position);

		bool colliding = (
			p->x < o->rect.x + o->rect.width &&
			p->x + circleRadius > o->rect.x &&
			p->y < o->rect.y + o->rect.height &&
			p->y + +circleRadius > o->rect.y
		);

		if (colliding) {
			collision = true;
			return;
		}
	}

	// Update Position
	bird->position.y += bird->speed * deltaTime;

	if (bird->position.y > SCREEN_HEIGHT) {
		bird->position.y = SCREEN_HEIGHT;
	}
	else if (bird->position.y < 0) {
		bird->position.y = 0;
		bird->speed = 0;
	}

	bird->speed += GRAVITY * deltaTime;


	
}

void GameManager::UpdateEnv(std::vector<Pipe>* aPipes, float deltaTime) {
	for (int i = 0; i < pipes.size(); i++) {
		pipes[i].rect.x -= (SCROLLING_SPEED * deltaTime);
	}

	//for (Pipe pipe : *pipes) {
	//	Pipe* pPipe = *pipe;
	//	pipe.rect.x -= (SCROLLING_SPEED * deltaTime);
	//	//std::cout << pipe->rect.x << std::endl;
	//}
}