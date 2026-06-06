#include <iostream>
#include "Grid.h"

void Grid::printGrid() {
	printEmptySpace(30);
	printLines();
	cout << endl;

	for (GridPoint point : grid) {
		cout << point.getChar();
		if (point.getX() == getGridX() - 1) {
			cout << endl;
		}
	}	

	printLines();
}

void Grid::printEmptySpace(int space) {
	for (int i = 0; i < space; i++) {
		cout << endl;
	}
}

void Grid::printLines() {
	for (int i = 0; i < getGridX(); i++) {
		cout << "-";
	}
}

GridPoint& Grid::getPoint(GridPoint pos) {
	bool inBounds = pos.getX() <= getGridX() && pos.getY() <= getGridY();
	if (!inBounds) {
		// return something
	}

	for (GridPoint& point : grid) {
		if (pos.getX() == point.getX() && pos.getY() == point.getY()) {
			return point;
		}
	}
}
