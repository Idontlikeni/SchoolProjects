#include <iostream>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <Windows.h>
#include "Player.h"
int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 16;				// World Dimensions
int nMapHeight = 16;
float fPlayerX = 14.7f;			// Player Start Position
float fPlayerY = 5.09f;
float fPlayerA = 0.0f;			// Player Start Rotation
float fFOV = 3.14159f / 4.0f;	// Field of View
float fDepth = 16.0f;			// Maximum rendering distance
float fSpeed = 50.0f;			// Walking Speed
float fGravity = 10.0f;
float fGravVel = 0.0f;
using namespace std;
int main()
{
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Create Map of world space # = wall block, . = space
	wstring map;
	map += L"#########.......";
	map += L"#...............";
	map += L"#.......########";
	map += L"#..............#";
	map += L"#......##......#";
	map += L"#......##......#";
	map += L"#..............#";
	map += L"###............#";
	map += L"##.............#";
	map += L"#......####..###";
	map += L"#......#.......#";
	map += L"#......#.......#";
	map += L"#..............#";
	map += L"#......#########";
	map += L"#@.............#";
	map += L"################";

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();
	int c = 0;

	Player player(5, 0, 3, screen);
	//Wall wall(11, 10, 5, 5, screen);
	vector<Wall> walls;
	walls.push_back(Wall(5, 35, 5, 5, screen));
	walls.push_back(Wall(10, 35, 5, 5, screen));
	walls.push_back(Wall(15, 35, 5, 5, screen));
	while (1)
	{
		// We'll need time differential per frame to calculate modification
		// to movement speeds, to ensure consistant movement, as ray-tracing
		// is non-deterministic
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();


		// Handle CCW Rotation
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			player.move(-fSpeed * fElapsedTime, 0, &wall);
			//fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;

		// Handle CW Rotation
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			player.move(fSpeed * fElapsedTime, 0, &wall);
			//fPlayerA += (fSpeed * 0.75f) * fElapsedTime;

		// Handle Forwards movement & collision
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			//player.move(0, -fSpeed * fElapsedTime);
			fGravVel = -200;
			/*fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
			fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
				fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
			}*/
		}
		player.move(0, fGravVel * fElapsedTime, &wall);
		// Handle backwards movement & collision
		//if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		//{
		//	player.move(0, fSpeed * fElapsedTime);
		//	/*fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
		//	fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
		//	if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
		//	{
		//		fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
		//		fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
		//	}*/
		//}

		for (int x = 0; x < nScreenWidth; x++)
		{
			// For each column, calculate the projected ray angle into world space

			// Incrementally cast ray from player, along ray angle, testing for 
			// intersection with a block
					// Ray is inbounds so test to see if the ray cell is a wall block
			//if (map.c_str()[nTestX * nMapWidth + nTestY] == '#')

			

			// Shader walls based on distance
			short nShade = ' ';
			//nShade = 0x2588;
			//if (fDistanceToWall <= fDepth / 4.0f)			nShade = 0x2588;	// Very close	
			//else if (fDistanceToWall < fDepth / 3.0f)		nShade = 0x2593;
			//else if (fDistanceToWall < fDepth / 2.0f)		nShade = 0x2592;
			//else if (fDistanceToWall < fDepth)				nShade = 0x2591;
			//else											nShade = ' ';		// Too far away

			//if (bBoundary)		nShade = ' '; // Black it out

			for (int y = 0; y < nScreenHeight; y++)
			{
				screen[y * nScreenWidth + x] = ' ';
			}
		}

		// Display Stats
		short nShade = ' ';
		nShade = 0x2588;
		swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);
		//screen[nScreenWidth + (c / 20 % nScreenWidth)] = nShade;
		player.draw();
		wall.draw();
		fGravVel = min(fGravVel + fGravity * fElapsedTime, 250.0f);
		// Display Map
		/*for (int nx = 0; nx < nMapWidth; nx++)
			for (int ny = 0; ny < nMapWidth; ny++)
			{
				screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
			}
		screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';*/

		// Display Frame
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	}

	return 0;
}

// That's It!! - Jx9