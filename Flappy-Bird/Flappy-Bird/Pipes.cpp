#include "Pipes.h"
#include "GameConstants.h"
#include <iostream>

std::vector<Pipe> GeneratePipes(int amount) {
	int offset = 0;
	std::vector<Pipe> pipes;

	for (int i = 0; i < amount; i++) {
		Pipe topPipe{};
		Pipe bottomPipe{};

		float x = (float)SCREEN_WIDTH + offset;
		// Generate top pipe
		float topPipeHeight = (float)(rand() % (SCREEN_HEIGHT - PIPE_GAP));
		topPipe.rect = { x, 0, PIPE_WIDTH, topPipeHeight };
		topPipe.color = GREEN;

		// Generate bottom pipe
		float bottomPipeY = topPipe.rect.y + PIPE_GAP + topPipe.rect.height;
		bottomPipe.rect = { x, bottomPipeY, PIPE_WIDTH, SCREEN_HEIGHT };
		bottomPipe.color = GREEN;

		pipes.push_back(topPipe);
		pipes.push_back(bottomPipe);

		offset += PIPE_X_GAP;
	}

	return pipes;
}