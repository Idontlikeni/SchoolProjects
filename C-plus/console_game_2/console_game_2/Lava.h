#pragma once
#include "Wall.h"
class Lava : public Wall
{
public:
	void draw() {
		short nShade = ' ';
		nShade = 0x2591;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++) {
				screen[(i + (int)y) * 120 + j + (int)x] = nShade;
			}
		}
	}
	Lava(float x, float y, int width, int height, wchar_t* screen) :Wall(x, y, width, height, screen) {}

};