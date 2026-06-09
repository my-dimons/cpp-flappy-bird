#pragma once

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr int FPS = 60;
constexpr bool DEBUG = true;

constexpr auto SCROLLING_SPEED = 300;

// BIRD
constexpr int BIRD_X_POS = 140;
constexpr float BIRD_JUMP_SPEED = 400.0f;
constexpr int GRAVITY = 800;

// PIPES
constexpr int PIPE_X_POS = SCREEN_WIDTH + 30;
constexpr int PIPE_GAP = 300;
constexpr int PIPE_WIDTH = 80;
constexpr int PIPE_TIME = 5;
constexpr int PIPE_X_GAP = 700;

struct GameConstants
{
	const char* windowName = "Flappy Bird";
};

