#pragma once
#include "raylib.h"
#include <vector>

struct Pipe {
	Rectangle rect;
	int blocking;
	Color color;
};

struct PipeSet {
	Pipe topPipe;
	Pipe bottomPipe;
};

PipeSet GeneratePipe();