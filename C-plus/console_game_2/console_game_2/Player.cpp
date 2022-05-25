#include "Player.h"

int Player::getLives()
{
	return lives;
}

void Player::draw()
{
	short nShade = 0x2588;
	for (int i = 0; i < width; i++)
	{
		screen[((int)y) * 120 + (int)x + i] = nShade;
		screen[((int)y + height - 1) * 120 + (int)x + i] = nShade;
	}
	for (int i = 1; i < height + 1; i++)
	{
		screen[((int)y + i) * 120 + (int)x] = nShade;
		screen[((int)y + i) * 120 + width - 1 +(int)x] = nShade;
	}
}

void Player::die()
{
	dead = true;
}

void Player::setLives(int lives)
{
	this->lives = lives;
}

bool Player::check_collisions(std::vector<Wall>& walls) {
	for (int i = 0; i < walls.size(); i++) {
		if (check_collision(walls[i])) {
			return true;
		}
	}
	return false;
}

bool Player::move(float dx, float dy, std::vector<Wall>& walls)
{
	x += dx;
	y += dy;
	if (check_collisions(walls)) {
		x -= dx;
		y -= dy;
		return true;
	}
	/*for (int i = 0; i < walls.size(); i++) {
		if (check_collision(walls[i])) {
			x -= dx;
			y -= dy;
			return true;
		}
	}*/
	
	return false;
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
}