#include "GameManager.h"
#include "GameConstants.h"
#include "raylib.h"
#include "Pipes.h"
#include <vector>
#include <iostream>

Bird bird = { 0 };
std::vector<PipeSet> pipes;

const float circleRadius = 58;
const float birdHitboxRadius = 30;

float timer;
int score;
int highscore;

int pipeTimer;

bool gameOver = false;

void GameManager::CloseGame() {
	CloseWindow();
}

void GameManager::InitGame() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowName);
	SetTargetFPS(FPS);

	RestartGame();
}

void GameManager::GameLoop() {
	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();
		timer += deltaTime;

		if (!gameOver) {
			if (IsKeyPressed(KEY_C)) {
				DEBUG = !DEBUG;
			}

			HandleScore();
			GeneratePipes();
			UpdatePlayer(&bird, deltaTime);
			UpdateEnv(&pipes, deltaTime);
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

void GameManager::HandleScore()
{
	if ((int)timer >= score) {
		score++;
	}
}

void GameManager::GeneratePipes()
{
	if ((int)(timer * 1000) >= (PIPE_TIME * pipeTimer)) {
		pipeTimer++;

		pipes.push_back(GeneratePipe());
	}
}

void GameManager::RenderFrame() {
	ClearBackground(RAYWHITE);

	RenderObjects();

	RenderText();
}

void GameManager::RestartGame() {
	//pipes = GeneratePipes(0);
	bird.position = { BIRD_X_POS, SCREEN_HEIGHT / 2 };
	bird.speed = 0;

	timer = 0;
	pipeTimer = 0;
	score = 0;
	pipes.clear();
}

void GameManager::RenderObjects() {
	// Draw player
	DrawCircleV(bird.position, circleRadius, SKYBLUE);

	if (DEBUG) {
		// Player hitbox
		DrawRectangle(
			bird.position.x - birdHitboxRadius,
			bird.position.y - birdHitboxRadius,
			birdHitboxRadius * 2,
			birdHitboxRadius * 2,
			RED);

		DrawLine(SCREEN_WIDTH / 2, -SCREEN_HEIGHT * 10, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 10, RED); // vertical line
		DrawLine(-SCREEN_WIDTH * 10, SCREEN_HEIGHT / 2, SCREEN_WIDTH * 10, SCREEN_HEIGHT / 2, RED); // horizontal line
	}

	
	for (const PipeSet pipe : pipes) {
		DrawRectangle(pipe.topPipe.rect.x, pipe.topPipe.rect.y, pipe.topPipe.rect.width, pipe.topPipe.rect.height, pipe.topPipe.color);
		DrawRectangle(pipe.bottomPipe.rect.x, pipe.bottomPipe.rect.y, pipe.bottomPipe.rect.width, pipe.bottomPipe.rect.height, pipe.bottomPipe.color);
	}
}

void GameManager::RenderText() {
	if (DEBUG)
		RenderDebugText();

	DrawText("Click 'Space' to jump", 10, 10, 20, DARKGRAY);
	DrawText("Click 'Esc' to quit", 10, 30, 20, DARKGRAY);
	DrawText(TextFormat("Score: %i", score), 10, 50, 20, DARKGRAY);

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
	const char* fpsText = TextFormat("FPS: %i/%i (%02.02f ms)", GetFPS(), FPS, GetFrameTime());
	DrawText(fpsText, 10, 100, 20, DARKGREEN);
	// Timer text
	const char* timerText = TextFormat("Timer: %03.0f ms", timer * 1000, FPS, GetFrameTime());
	DrawText(timerText, 10, 130, 20, DARKGREEN);
}

void GameManager::UpdatePlayer(Bird* bird, float deltaTime) {
	if (IsKeyPressed(KEY_SPACE)) {
		bird->speed = -BIRD_JUMP_SPEED;
	}

	// Collision detection
	for (int i = 0; i < pipes.size(); i++) {
		PipeSet* o = &pipes[i];
		Rectangle* pRect = new Rectangle(
			bird->position.x - birdHitboxRadius,
			bird->position.y - birdHitboxRadius,
			birdHitboxRadius * 2,
			birdHitboxRadius * 2);

		bool colliding = 
			IsColliding(pRect, &(o->topPipe.rect)) || 
			IsColliding(pRect, &(o->bottomPipe.rect)) || 
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

void GameManager::UpdateEnv(std::vector<PipeSet>* aPipes, float deltaTime) {
	for (int i = 0; i < pipes.size(); i++) {
		if (pipes[i].topPipe.rect.x + pipes[i].topPipe.rect.width < 0) {
			pipes.erase(pipes.begin() + i);
		}

		float movement = (SCROLLING_SPEED * deltaTime);
		pipes[i].topPipe.rect.x -= movement;
		pipes[i].bottomPipe.rect.x -= movement;
	}
}