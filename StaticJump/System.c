#include "System.h"

void Init()
{
	system("title Static Jump (English)");
	system("mode con cols=140 lines=55");

	CONSOLE_CURSOR_INFO consoleCursorInfo;

	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	srand((unsigned int)time(NULL));
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int Input()
{
	return _kbhit() ? _getch() : -2;
}

void Delay(clock_t waitTIme)
{
	clock_t start = clock();

	while (clock() - start < waitTIme);
}