#pragma once
#include "Wall.h"
class Player: public Entity
{
private:
	int lives, max_lives;
	bool dead, new_lvl;
	wchar_t* screen; 

public:
	short nShade;
	int getLives();
	bool is_new();
	bool is_dead();
	void arise();
	void lvl_swotched();
	virtual void draw();
	virtual int check_collision(Entity& entity);
	void die();
	void setLives(int lives);
	bool check_collisions(std::vector<Entity*>& walls);
	bool move(float dx, float dy, std::vector<Entity*>& walls);
	Player(float x, float y, int lives, wchar_t* screen);
};

