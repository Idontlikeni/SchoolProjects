// Game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 0.0f;
float fPlayerY = 0.0f;

int nMapHeight = 28;
int nMapWidth = 64;

int playerX = 1;
int playerY = 1;

int main()
{
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	char gradient[] = " .:!/r(l1Z4H9W8$@";

	wstring map;
	map += L"################################################################";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"#..............................................................#";
	map += L"################################################################";
	while (1) {
		this_thread::sleep_for(50ms);
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			//fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;
			playerX--;

		// Handle CW Rotation
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			//fPlayerA += (fSpeed * 0.75f) * fElapsedTime;
			playerX++;

		// Handle Forwards movement & collision
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			playerY--;
			/*fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
			fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
				fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
			}*/
		}

		// Handle backwards movement & collision
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			playerY++;
			/*fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
			fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
				fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
			}*/
		}

		map[playerY * nMapWidth + playerX] = '@';

		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				screen[y * nScreenWidth + x] = map[y * nMapWidth + x];
			}
		}
		
		//screen[playerY * nScreenWidth + playerX] = map[playerY * nMapWidth + playerX];

		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
