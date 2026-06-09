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
const float birdHitboxRadius = 30;

float timer;
int score;
int highscore;

bool gameOver = false;

void GameManager::CloseGame() {
	CloseWindow();
}

void GameManager::InitGame() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, gameConstants.windowName);
	SetTargetFPS(0);

	RestartGame();
}

void GameManager::GameLoop() {
	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();
		timer += deltaTime;

		if (!gameOver) {
			UpdatePlayer(&bird, deltaTime);
			UpdateEnv(&pipes, deltaTime);

			if ((int)timer >= score) {
				score++;
			}
		} else {
			if (IsKeyPressed(KEY_V)) {
				RestartGame();
				gameOver = false;
			}	
			
			if (score > highscore) {
				highscore = score;
			}
		}

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

void GameManager::RestartGame() {
	pipes = GeneratePipes(100000);
	bird.position = { BIRD_X_POS, SCREEN_HEIGHT / 2 };
	bird.speed = 0;

	timer = 0;
	score = 0;
}

void GameManager::RenderObjects() {
	// Draw bird
	DrawCircleV(bird.position, circleRadius, SKYBLUE);
	if (DEBUG) {
		DrawRectangle(
			bird.position.x - birdHitboxRadius,
			bird.position.y - birdHitboxRadius,
			birdHitboxRadius * 2,
			birdHitboxRadius * 2,
			RED);
	}

	for (const Pipe pipe : pipes) {
		DrawRectangle(pipe.rect.x, pipe.rect.y, pipe.rect.width, pipe.rect.height, pipe.color);
	}
	DrawLine(SCREEN_WIDTH / 2, -SCREEN_HEIGHT * 10, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 10, RED); // vertical line
	DrawLine(-SCREEN_WIDTH * 10, SCREEN_HEIGHT / 2, SCREEN_WIDTH * 10, SCREEN_HEIGHT / 2, RED); // horizontal line
}

void GameManager::RenderText() {
	if (DEBUG)
		RenderDebugText();

	DrawText("Click 'Space' to jump", 10, 10, 20, DARKGRAY);
	DrawText("Click 'Esc' to quit", 10, 30, 20, DARKGRAY);
	DrawText(TextFormat("Score: %i", score), 10, 50, 20, DARKGRAY);
	const char* fpsText = TextFormat("FPS: %i/%i (%02.02f ms)", GetFPS(), FPS, GetFrameTime());
	DrawText(fpsText, 10, 100, 20, DARKGREEN);

	if (gameOver) {
		float size = 60;
		const char* text = "GAME OVER!";
		DrawText(text, (SCREEN_WIDTH / 2) - (MeasureText(text, size) / 2), (SCREEN_HEIGHT / 2) - size, size, BLACK);

		float size2 = 40;
		const char* text2 = TextFormat(("Score: %i (Highscore: %i)"), score, highscore);

		DrawText(text2, (SCREEN_WIDTH / 2) - (MeasureText(text2, size2) / 2), (SCREEN_HEIGHT / 2), size2, GRAY);

		float size3 = 30;
		const char* text3 = ("Click 'V' to play again!");
		DrawText(text3, (SCREEN_WIDTH / 2) - (MeasureText(text3, size3) / 2), (SCREEN_HEIGHT / 2) + size2, size3, GRAY);
	}
}

void GameManager::RenderDebugText() {
	// FPS Text

	const char* timerText = TextFormat("Timer: %03.0f ms", timer * 1000, FPS, GetFrameTime());
	DrawText(timerText, 10, 130, 20, DARKGREEN);
}

void GameManager::UpdatePlayer(Bird* bird, float deltaTime) {
	if (IsKeyPressed(KEY_SPACE)) {
		bird->speed = -BIRD_JUMP_SPEED;
	}

	// Collision detection
	for (int i = 0; i < pipes.size(); i++) {
		Pipe* o = &pipes[i];
		Rectangle* pRect = new Rectangle(
			bird->position.x - birdHitboxRadius,
			bird->position.y - birdHitboxRadius,
			birdHitboxRadius * 2,
			birdHitboxRadius * 2);

		bool colliding = 
			IsColliding(pRect, &(o->rect)) || 
			bird->position.y >= SCREEN_HEIGHT;

		if (colliding) {
			gameOver = true;
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

bool GameManager::IsColliding(Rectangle* dx, Rectangle* dy) {
	return
		dx->x < dy->x + dy->width &&
		dx->x + dx->width > dy->x &&
		dx->y < dy->y + dy->height &&
		dx->y + dx->height > dy->y;
}

void GameManager::UpdateEnv(std::vector<Pipe>* aPipes, float deltaTime) {
	for (int i = 0; i < pipes.size(); i++) {
		pipes[i].rect.x -= (SCROLLING_SPEED * deltaTime);
	}
}