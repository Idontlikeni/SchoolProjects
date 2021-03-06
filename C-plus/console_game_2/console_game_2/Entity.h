#pragma once
#include<algorithm>
#include <vector>
class Entity
{
protected:
	float x, y;
	int width, height, id;
	bool dead;
	wchar_t* screen;
	virtual int check_collision(Entity& entity);
	virtual bool check_collisions();
public:
	float getX();
	float getY();
	int getId();
	virtual void draw();
	void die();
	void setPos(float x, float y);
	void setX(float x);
	void setY(float y);
	Entity(float x, float y, int width, int height, wchar_t* screen);
	Entity();
	~Entity();
};

