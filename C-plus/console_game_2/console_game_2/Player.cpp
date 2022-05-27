#include "Player.h"

int Player::getLives()
{
	return lives;
}

void Player::draw()
{
	//nShade = 0x2588;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			screen[(i + (int)y) * 120 + j + (int)x] = nShade;
		}
	}
	/*for (int i = 0; i < width; i++)
	{
		screen[((int)y) * 120 + (int)x + i] = nShade;
		screen[((int)y + height - 1) * 120 + (int)x + i] = nShade;
	}
	for (int i = 1; i < height - 1; i++)
	{
		screen[((int)y + i) * 120 + (int)x] = nShade;
		screen[((int)y + i) * 120 + width - 1 +(int)x] = nShade;
	}*/
}

void Player::die()
{
	dead = true;
}

void Player::setLives(int lives)
{
	this->lives = lives;
}

int Player::check_collision(Entity& entity) {
	if (Entity::check_collision(entity)) {
		return entity.getId();
	}
	else return 0;
}

bool Player::check_collisions(std::vector<Entity*>& walls) {
	bool coll = false;
	for (int i = 0; i < walls.size(); i++) {
		switch (check_collision(*walls[i]))
		{
			case 1:
				new_lvl = true;
				break;
			case 2:
				dead = true;
				break;
			case 3:
				coll = true;
				break;
			default:
				break;
		}
		/*if (check_collision(*walls[i])) {
			return true;
		}*/
	}
	return coll;
}

bool Player::move(float dx, float dy, std::vector<Entity*>& walls)
{
	x += dx;
	y += dy;
	if (check_collisions(walls)) {
		x -= dx;
		y -= dy;
		return true;
	}
	return false;
}

bool Player::is_new() {
	return new_lvl;
}

bool Player::is_dead() {
	return dead;
}

void Player::arise() {
	dead = false;
}

void Player::lvl_swotched() {
	new_lvl = false;
}

Player::Player(float x, float y, int lives, wchar_t* screen)
{
	this->x = x;
	this->y = y;
	this->lives = lives;
	this->max_lives = lives;
	this->screen = screen;
	dead = false;
	width = 5;
	height = 3;
	nShade = 0x2588;
	new_lvl = false;
}