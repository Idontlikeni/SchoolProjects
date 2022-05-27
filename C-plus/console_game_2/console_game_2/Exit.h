#pragma once
#include "Entity.h"
class Exit : public Entity
{
public:
	bool exit;
	Exit(float x, float y, int width, int height, wchar_t* screen) :Entity(x, y, width, height, screen) {}
};


