#include "GameManager.h"
#include <iostream>

int main() {
	GameManager* manager = new GameManager();

	manager->InitGame();

	manager->GameLoop();

	manager->CloseGame();

	return 0;
}