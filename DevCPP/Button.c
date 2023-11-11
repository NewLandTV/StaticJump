#include "Button.h"

INPUT_RECORD inputRecord;
DWORD dwNumberOfEventsRead;

void DrawButton(Button button)
{
	int x;
	int y;
	
	for (y = button.position.y; y < button.position.y + button.scale.y; y++)
	{
		for (x = button.position.x; x < button.position.x + button.scale.x; x++)
		{
			Gotoxy(x, y);
			
			printf("%c", button.backgroundSprite);
		}
	}
	
	Gotoxy(button.position.x + ShortMax(button.scale.x - strlen(button.text), strlen(button.text) - button.scale.x) / 2, button.position.y + button.scale.y / 2);
	
	printf("%s", button.text);
}

USHORT CheckClick(Button button)
{
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);
	
	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			int buttonX;
			int buttonY;
			int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;

			for (buttonY = button.position.y; buttonY < button.position.y + button.scale.y; buttonY++)
			{
				for (buttonX = button.position.x; buttonX < button.position.x + button.scale.x; buttonX++)
				{
					if (buttonX == mouseX && buttonY == mouseY)
					{
						HANDLE consoleIn;
						DWORD mode;
						
						consoleIn = GetStdHandle(STD_INPUT_HANDLE);
						
						GetConsoleMode(consoleIn, &mode);
						SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);
						
						return 1;
					}
				}
			}
		}
	}
	
	return 0;
}
