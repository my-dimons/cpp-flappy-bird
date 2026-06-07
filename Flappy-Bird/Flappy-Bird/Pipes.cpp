#include "Pipes.h"
#include "GameConstants.h"
#include <iostream>

std::vector<Pipe*> GeneratePipes(int amount) {
	int offset = 0;
	std::vector<Pipe*> pipes;

	for (int i = 0; i < amount; i++) {
		Pipe topPipe;
		Pipe* bottomPipe = new Pipe();

		// Generate pipe 1
		topPipe.rect = { (float)SCREEN_WIDTH + offset, 300, PIPE_WIDTH, 300 };
		topPipe.color = GREEN;

		std::cout << topPipe.rect.x;
		pipes.push_back(&topPipe);
		offset += PIPE_X_GAP;
	}

	return pipes;
}