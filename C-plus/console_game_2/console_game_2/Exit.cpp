#include "Exit.h"
Exit::Exit(float x, float y, int width, int height, wchar_t* screen) :Entity(x, y, width, height, screen) {
	exit = true;
}