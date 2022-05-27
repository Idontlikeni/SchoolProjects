#include "Wall.h"

Wall::Wall(float x, float y, int width, int height, wchar_t* screen) :Entity(x, y, width, height, screen)
{
	id = 3;
}
