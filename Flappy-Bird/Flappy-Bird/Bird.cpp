#include "Bird.h"

int physicsCounter = 0;

void Bird::Object::Update() {
	// Apply physics
	physicsCounter++;
	
	if (physicsCounter >= Bird::gravity) {
		GridPoint newPos(pos.getX(), pos.getY() - 1);
		setPos(newPos);
	}
}