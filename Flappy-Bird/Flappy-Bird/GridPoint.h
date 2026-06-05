#pragma once

struct GridPoint {
public:
	GridPoint(int aX, int aY) {
		x = aX;
		y = aY;
	}

	void setX(int aX) { x = aX; }
	void setY(int aY) { y = aY; }
	void setChar(char aChar) { character = aChar; }
	int getX() const { return x; }
	int getY() const { return y; }
	char getChar() const { return character; }
private:
	int x = 0;
	int y = 0;
	char character = '*';
};