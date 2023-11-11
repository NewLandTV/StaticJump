#include "Button.h"

void DrawButton(const Button* button)
{
	int x;
	int y;

	if (button->backgroundSprite != ' ')
	{
		for (y = button->position.y; y < button->position.y + button->scale.y; y++)
		{
			for (x = button->position.x; x < button->position.x + button->scale.x; x++)
			{
				Gotoxy(x, y);
				printf("%c", button->backgroundSprite);
			}
		}
	}
	else
	{
		Gotoxy(button->position.x - 1, button->position.y);
		printf("¦£");
		Gotoxy(button->position.x + button->scale.x - 1, button->position.y);
		printf("¦¤");
		Gotoxy(button->position.x - 1, button->position.y + button->scale.y - 1);
		printf("¦¦");
		Gotoxy(button->position.x + button->scale.x - 1, button->position.y + button->scale.y - 1);
		printf("¦¥");

		for (x = button->position.x; x < button->position.x + button->scale.x - 1; x += 2)
		{
			Gotoxy(x, button->position.y);
			printf("¦¡");
			Gotoxy(x, button->position.y + button->scale.y - 1);
			printf("¦¡");
		}

		for (y = button->position.y + 1; y < button->position.y + button->scale.y - 1; y++)
		{
			Gotoxy(button->position.x - 1, y);
			printf("¦¢");
			Gotoxy(button->position.x + button->scale.x - 1, y);
			printf("¦¢");
		}
	}

	Gotoxy(button->position.x + (ShortMax(button->scale.x - strlen(button->text), strlen(button->text) - button->scale.x) >> 1), button->position.y + (button->scale.y >> 1));
	printf("%s", button->text);
}

int CheckClick(const Button* button)
{
	INPUT_RECORD inputRecord;
	DWORD dwNumberOfEventsRead;
	HANDLE consoleIn;
	DWORD mode;

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);

	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED && !(inputRecord.Event.MouseEvent.dwEventFlags & MOUSE_MOVED) && !(inputRecord.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK))
		{
			int buttonX;
			int buttonY;
			int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;

			if (button->position.x <= mouseX && mouseX < button->position.x + button->scale.x && button->position.y <= mouseY && mouseY < button->position.y + button->scale.y)
			{
				consoleIn = GetStdHandle(STD_INPUT_HANDLE);

				GetConsoleMode(consoleIn, &mode);
				SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);

				return 1;
			}
		}
	}

	consoleIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(consoleIn, &mode);
	SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);

	return 0;
}