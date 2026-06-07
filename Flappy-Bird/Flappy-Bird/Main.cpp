#include "GameManager.h"
#include <iostream>

int main() {
	GameManager manager;

  manager.InitGame();
	manager.GameLoop();
	manager.CloseGame();

	return 0;
}