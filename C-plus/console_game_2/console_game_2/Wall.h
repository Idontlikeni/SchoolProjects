#pragma once
#include "Entity.h"
class Wall: public Entity
{
public:
	Wall(float x, float y, int width, int height, wchar_t* screen) :Entity(x, y, width, height, screen) {}
};