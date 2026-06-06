#pragma once
#include "GridPoint.h"

class Object {
public:
	Object();
	void Update();
	void Start();
	GridPoint getPos() const { return pos; }
	void setPos(GridPoint pos) { this->pos = pos; }
	void updateGridPoint() {
		gridPoint.setX(pos.getX());
		gridPoint.setY(pos.getY());
		gridPoint.setChar(pos.getChar());
	}
protected:
	GridPoint pos;
	GridPoint& gridPoint;
};