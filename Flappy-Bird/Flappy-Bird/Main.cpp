#include "GameManager.h"
#include <iostream>

int main() {
	srand(time(0));

	GameManager manager;

  manager.InitGame();
	manager.GameLoop();
	manager.CloseGame();

	return 0;
}