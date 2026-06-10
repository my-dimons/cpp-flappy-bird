#pragma once

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 600;
constexpr int FPS = 60;
static bool DEBUG = false;

constexpr auto SCROLLING_SPEED = 300;

// BIRD
constexpr int BIRD_X_POS = 140;
constexpr float BIRD_JUMP_SPEED = 400.0f;
constexpr int GRAVITY = 800;

// PIPES
constexpr int PIPE_GAP = 200;
constexpr int PIPE_WIDTH = 80;
constexpr int PIPE_TIME = 2000; // in milliseconds
constexpr int PIPE_X_GAP = 700;

static const char* windowName = "Flappy Bird";
