#pragma once
#include "GridPoint.h"
#include <vector>
#include <iostream>

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
	static int getGridX() { return gridX; }
	static int getGridY() { return gridY; }
	GridPoint& getPoint(GridPoint point);
	int setPointChar(GridPoint& point, char aChar) { point.setChar(aChar); }
private:
	static void printLines();
	static void printEmptySpace(int space);
	static int const gridX = 100;
	static int const gridY = 30;
	vector<GridPoint> grid;
};