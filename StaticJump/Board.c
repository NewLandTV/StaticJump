#include "Board.h"

void DrawBoard(const Vector2* leftTop, const Vector2* rightBottom)
{
	int x;
	int y;

	Gotoxy(leftTop->x, leftTop->y);
	printf("¦£");
	Gotoxy(rightBottom->x - 2, leftTop->y);
	printf("¦¤");
	Gotoxy(leftTop->x, rightBottom->y - 1);
	printf("¦¦");
	Gotoxy(rightBottom->x - 2, rightBottom->y - 1);
	printf("¦¥");

	for (x = leftTop->x + 2; x < rightBottom->x - 2; x += 2)
	{
		Gotoxy(x, leftTop->y);
		printf("¦¡");
		Gotoxy(x, rightBottom->y - 1);
		printf("¦¡");
	}

	for (y = leftTop->y + 1; y < rightBottom->y - 1; y++)
	{
		Gotoxy(leftTop->x, y);
		printf("¦¢");
		Gotoxy(rightBottom->x - 2, y);
		printf("¦¢");
	}
}