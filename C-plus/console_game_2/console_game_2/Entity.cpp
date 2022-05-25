#include "Entity.h"
bool Entity::check_collision(Entity& entity)
{
	float selfx2 = x + width;
	float selfy2 = y + height;

	float x1 = entity.x;
	float y1 = entity.y;
	float x2 = entity.x + entity.width;
	float y2 = entity.y + entity.height;
	return (x < x2 && selfx2 > x1 && y < y2 && selfy2 > y1);
}

bool Entity::check_collisions()
{
	return false;
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

void Entity::draw()
{
	short nShade = ' ';
	nShade = 0x2593;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			screen[(i + (int)y) * 120 + j + (int)x] = nShade;
		}
	}
}

void Entity::die()
{
	dead = true;
}

void Entity::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Entity::setX(float x)
{
	this->x = x;
}

void Entity::setY(float y)
{
	this->y = y;
}


Entity::Entity(float x, float y, int width, int height, wchar_t* screen)
{
	this->x = x;
	this->y = y;
	this->screen = screen;
	dead = false;
	this->width = width;
	this->height = height;
}

Entity::Entity()
{
	x = 0;
	y = 0;
	screen = nullptr;
	dead = false;
	width = 0;
	height = 0;
}
