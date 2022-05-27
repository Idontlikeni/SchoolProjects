#include <iostream>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <Windows.h>
#include <tuple>
#include "Player.h"
#include "Lava.h"
#include "Exit.h"
int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 24;				// World Dimensions
int nMapHeight = 8;
float fPlayerX = 14.7f;			// Player Start Position
float fPlayerY = 5.09f;
float fPlayerA = 0.0f;			// Player Start Rotation
float fFOV = 3.14159f / 4.0f;	// Field of View
float fDepth = 16.0f;			// Maximum rendering distance
float fSpeed = 50.0f;			// Walking Speed
float fGravity = 120.0f;
float fGravVel = 0.0f;
using namespace std;
tuple<int, int> generate_map(wstring& map, vector<Entity*>& walls, wchar_t* screen) {
	tuple<int, int> pos;
	
	for (int nx = 0; nx < nMapWidth; nx++)
		for (int ny = 0; ny < nMapHeight; ny++)
		{
			if (map[ny * nMapWidth + nx] == '#') {
				walls.push_back(new Wall(nx * 5, ny * 4, 5, 4, screen));
			}
			else if (map[ny * nMapWidth + nx] == '@') {
				pos = make_tuple(nx * 5, ny * 4);
			}
			else if (map[ny * nMapWidth + nx] == 'l') {
				walls.push_back(new Lava(nx * 5, ny * 4, 5, 4, screen));
			}
			else if (map[ny * nMapWidth + nx] == 'e') {
				walls.push_back(new Exit(nx * 5, ny * 4 - 1, 5, 5, screen));
			}
		}
	return pos;
}
int main()
{
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	bool in_air = false;
	// Create Map of world space # = wall block, . = space
	vector <wstring>maps;
	wstring map;
	int curr_map = 0;
	map += L"#......................#";
	map += L"#......##......#.......#";
	map += L"###............#...@...#";
	map += L"##............e#.......#";
	map += L"#......#########.......#";
	map += L"#......................#";
	map += L"#......................#";
	map += L"#######lllllllll########";
	maps.push_back(map);

	map = L"";
	map += L"#......................#";
	map += L"#......................#";
	map += L"#......................#";
	map += L"#...e...........###....#";
	map += L"#...###................#";
	map += L"#.........###.........@#";
	map += L"#......................#";
	map += L"#lllllllllllllllllll####";
	maps.push_back(map);

	map = L"";
	map += L"#......................#";
	map += L"#...####..#...#..###...#";
	map += L"#...#.....##..#..#..#..#";
	map += L"#...####..#.#.#..#..#..#";
	map += L"#...#.....#..##..#..#..#";
	map += L"#...####..#...#..###...#";
	map += L"#...........@..........#";
	map += L"########################";
	maps.push_back(map);

	map = L"";
	map += L"#......................#";
	map += L"#......##......#.......#";
	map += L"###............#...@...#";
	map += L"##............e#.......#";
	map += L"#......#########.......#";
	map += L"#......................#";
	map += L"#......................#";
	map += L"#######lllllllll########";

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();
	int c = 0;

	Player player(5, 0, 3, screen);
	vector<Entity *> walls;
	/*for (int nx = 0; nx < nMapWidth; nx++)
		for (int ny = 0; ny < nMapHeight; ny++)
		{
			if (map[ny * nMapWidth + nx] == '#') {
				walls.push_back(new Wall(nx * 5, ny * 4, 5, 4, screen));
			}
			else if (map[ny * nMapWidth + nx] == '@') {
				player.setPos(nx * 5, ny * 4);
			}
			else if (map[ny * nMapWidth + nx] == 'l') {
				walls.push_back(new Lava(nx * 5, ny * 4, 5, 4, screen));
			}
			else if (map[ny * nMapWidth + nx] == 'e') {
				walls.push_back(new Exit(nx * 5, ny * 4 - 1, 5, 5, screen));
			}

		}*/
	tuple<int, int> pos = generate_map(map, walls, screen);
	player.setPos(get<0>(pos), get<1>(pos));
	//walls.push_back(Lava(12, 12, 12, 112, screen));
	/*walls.push_back(Wall(5, 20, 5, 5, screen));
	walls.push_back(Wall(10, 20, 5, 5, screen));
	walls.push_back(Wall(15, 20, 5, 5, screen));
	walls.push_back(Wall(20, 20, 5, 5, screen));*/
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
			player.move(-fSpeed * fElapsedTime, 0, walls);
			//fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;

		// Handle CW Rotation
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			player.move(fSpeed * fElapsedTime, 0, walls);
			//fPlayerA += (fSpeed * 0.75f) * fElapsedTime;

		// Handle Forwards movement & collision
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			//player.move(0, -fSpeed * fElapsedTime, walls);
			//if(player)
			//player.setY(player.getY() + 1);
			if (player.check_collisions(walls)) { 
				fGravVel = -39; 
				in_air = true;
			}
			//player.setY(player.getY() - 1);
		}

		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			player.move(0, fSpeed * fElapsedTime, walls);
		}

		//player.setY(player.getY() + 1);
		//if (player.check_collisions(walls))fGravVel = 0;
		//player.setY(player.getY() - 1);

		if (player.move(0, fGravVel * fElapsedTime, walls)) {
  			//player.nShade = 0x2592;
			if (GetAsyncKeyState((unsigned short)'W') & 0x8000 || GetAsyncKeyState((unsigned short)' ') & 0x8000)
			{
				//player.move(0, -fSpeed * fElapsedTime, walls);
				//if(player)
				//player.setY(player.getY() + 1);
				//if (player.check_collisions(walls)) {
				fGravVel = -50;
				in_air = true;
				//}
				//player.setY(player.getY() - 1);
			}else fGravVel = 1;
		}
		/*else {
			player.nShade = 0x2588;
		}*/
		
		



		for (int x = 0; x < nScreenWidth; x++)
		{

			

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
		
		//screen[nScreenWidth + (c / 20 % nScreenWidth)] = nShade;
		player.draw();
		for (Entity* i: walls) {
			i->draw();
		}
		//wall.draw();
		fGravVel = min(fGravVel + fGravity * fElapsedTime, 200.0f);

		// Display Map
		/*for (int nx = 0; nx < nMapWidth; nx++)
			for (int ny = 0; ny < nMapWidth; ny++)
			{
				screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
			}
		screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';*/

		// Display Frame
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		if (player.is_dead()) {
			player.setPos(get<0>(pos), get<1>(pos));
			player.arise();
			fGravVel = 0;
		}

		if (player.is_new()) {
			curr_map = (curr_map + 1) % 3;
			for (auto p : walls)
			{
				delete p;
			}
			walls.clear();
			pos = generate_map(maps[curr_map] , walls, screen);
			player.setPos(get<0>(pos), get<1>(pos));
			player.lvl_swotched();//swotched XD
			fGravVel = 0;
		}
		swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, FPS=%3.2f ", player.getX(), player.getY(), 1.0f / fElapsedTime);
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	}

	return 0;
}