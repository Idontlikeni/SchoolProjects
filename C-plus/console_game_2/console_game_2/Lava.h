#pragma once
#include "Entity.h"
class Lava : public Entity
{
public:
	
	virtual void draw();
	Lava(float x, float y, int width, int height, wchar_t* screen);

};