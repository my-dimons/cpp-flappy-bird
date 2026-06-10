#include "Pipes.h"
#include "GameConstants.h"
#include <iostream>

std::vector<Pipe> GeneratePipe() {
	Pipe topPipe{};
	Pipe bottomPipe{};

	float x = SCREEN_WIDTH;
	float topPipeHeight = (float)(rand() % (SCREEN_HEIGHT - PIPE_GAP));
	topPipe.rect = { x, 0, PIPE_WIDTH, topPipeHeight };
	topPipe.color = GREEN;

	float bottomPipeY = topPipe.rect.y + PIPE_GAP + topPipe.rect.height;
	bottomPipe.rect = { x, bottomPipeY, PIPE_WIDTH, SCREEN_HEIGHT };
	bottomPipe.color = GREEN;

	return { topPipe, bottomPipe };
}
