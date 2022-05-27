#pragma once
#include "Entity.h"
class Exit : public Entity
{
public:
	bool exit;
	virtual void draw();
	Exit(float x, float y, int width, int height, wchar_t* screen);
};


