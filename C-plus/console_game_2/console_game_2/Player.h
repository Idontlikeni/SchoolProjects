#pragma once
#include "Wall.h"
class Player: public Entity
{
private:
	int lives, max_lives;
	bool dead;
	wchar_t* screen; 
public:
	int getLives();
	void draw();
	void die();
	void setLives(int lives);
	bool check_collisions(std::vector<Wall>& walls);
	bool move(float dx, float dy, std::vector<Wall>& walls);
	Player(float x, float y, int lives, wchar_t* screen);
};

