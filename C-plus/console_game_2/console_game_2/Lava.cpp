#include "Lava.h"
void Lava::draw() {
	short nShade = ' ';
	nShade = 0x2592;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			screen[(i + (int)y) * 120 + j + (int)x] = nShade;
		}
	}
}

Lava::Lava(float x, float y, int width, int height, wchar_t* screen) :Entity(x, y, width, height, screen)
{
	id = 2;
}
