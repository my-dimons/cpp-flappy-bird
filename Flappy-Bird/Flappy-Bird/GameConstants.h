#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define FPS 60
#define DRAW_DEBUG_TEXT true

#define SCROLLING_SPEED 300
// BIRD
#define BIRD_X_POS 80
#define BIRD_JUMP_SPEED 350.0f
#define GRAVITY 800

// PIPES
#define PIPE_X_POS SCREEN_WIDTH + 30
#define PIPE_GAP 50
#define PIPE_WIDTH 40
#define PIPE_TIME 5
#define PIPE_X_GAP 300

struct GameConstants
{
	const char* windowName = "Flappy Bird";
};

