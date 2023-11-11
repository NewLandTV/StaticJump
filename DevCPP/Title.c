#include "Title.h"

NoteMap* currentNoteMap;

NoteMap Title()
{
	NoteMap testNoteMap =
	{
		"test", "C:\\NewLand\\StaticJump\\NoteMap\\test.mp3", "NewLand Melodic Artist", "JkhTV", "80|30|60"
	};
	
	currentNoteMap = &testNoteMap;
	
	SaveNoteMap("test.sjnotmp", *currentNoteMap);
	ShowNoteMapInfo("test.sjnotmp");
	
	Gotoxy(CONSOLE_WIDTH / 2 - 7, 5);
	printf("PRESS ANY KEY");
	
	while (!_kbhit());
	
	system("cls");
	
	return *currentNoteMap;
}
