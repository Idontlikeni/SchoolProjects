#include "Exit.h"
void Exit::draw() {
	short nShade = ' ';
	nShade = 0x2588;
	for (int i = 0; i < height; i++)
	{
		screen[(i + (int)y) * 120 + height / 2 + (int)x] = nShade;
	}

	for (int j = 0; j < width; j++) {
		screen[(width / 2 + (int)y) * 120 + j + (int)x] = nShade;
	}
}

Exit::Exit(float x, float y, int width, int height, wchar_t* screen) :Entity(x, y, width, height, screen)
{
	id = 1;
	exit = true;
}
