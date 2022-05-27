#pragma once
#include "Wall.h"
class Player: public Entity
{
private:
	int lives, max_lives;
	bool dead;
	wchar_t* screen; 

public:
	short nShade;
	int getLives();
	void draw();
	void die();
	void setLives(int lives);
	bool check_collisions(std::vector<Entity*>& walls);
	bool move(float dx, float dy, std::vector<Entity*>& walls);
	Player(float x, float y, int lives, wchar_t* screen);
};

