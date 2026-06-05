#pragma once
#include "GridPoint.h"
#include <vector>

using namespace std;

class Grid {
public:
	Grid() {
		for (int i = 0; i < gridY; i++) {
			for (int j = 0; j < gridX; j++) {
				GridPoint gridPoint(j, i);
				grid.push_back(gridPoint);
			}
		}

		cout << "Generating Grid...";
	}
	void printGrid();
	int getGridX() const { return gridX; }
	int getGridY() const { return gridY; }
	int setPointChar(GridPoint& point, char aChar) { point.setChar(aChar); }
private:
	void printLines();
	void printEmptySpace(int space);
	int const gridX = 100;
	int const gridY = 30;
	vector<GridPoint> grid;
};