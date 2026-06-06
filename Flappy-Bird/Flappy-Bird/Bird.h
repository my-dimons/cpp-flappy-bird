#pragma once
#include "Object.h"
#include "Grid.h"

class Bird : Object {
public:
	Bird(Grid& grid) : startY(Grid::getGridY() / 2) {
		// Set initial position
		GridPoint startPos(x, startY);
		pos = startPos;
		pos.setChar(character);
	}

	/// <summary>
	/// Amount of frames that need to pass for the bird to fall 1 pos
	/// </summary>
	static int const gravity = 2;
	static int const x = 3;
	int const startY = 0;
private:
	static char const character = '/';
};