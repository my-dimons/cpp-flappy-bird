#include <iostream>
#include "Grid.h"

void Grid::printGrid() {
	printEmptySpace(30);
	printLines();
	cout << endl;

	for (GridPoint point : grid) {
		cout << "*";
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
