#include "NoteMapEditor.h"

void Setup()
{
	system("title Static Jump (English) - Note Map Editor");
}

void NoteMapEditor()
{
	NoteMap noteMap =
	{
		"", "", "", "", ""
	};

	short bpm = 0;
	short noteDropSpeed = 0;
	short noteCount = 0;
	char tempNoteData[15] = "0|0|0";
	char nameInput[1024];
	char musicFilePathInput[1024];
	char composerNameInput[1024];
	char creatorNameInput[1024];
	char* path;

	printf("Name : ");
	scanf_s(" %[^\n]s", nameInput, sizeof(nameInput));

	noteMap.name = nameInput;

	path = (char*)malloc((sizeof(char) * (strlen(noteMap.name) + strlen(NOTE_MAP_FILE_EXTENSION))) + 1);

	strcpy_s(path, (sizeof(char) * (strlen(noteMap.name) + strlen(NOTE_MAP_FILE_EXTENSION))) + 1, noteMap.name);
	strcat_s(path, (sizeof(char) * (strlen(noteMap.name) + strlen(NOTE_MAP_FILE_EXTENSION))) + 1, NOTE_MAP_FILE_EXTENSION);

	printf("Music File Path : ");
	scanf_s(" %[^\n]s", musicFilePathInput, sizeof(musicFilePathInput));

	noteMap.musicFilePath = musicFilePathInput;

	printf("Composer Name : ");
	scanf_s(" %[^\n]s", composerNameInput, sizeof(composerNameInput));

	noteMap.composerName = composerNameInput;

	printf("Creator Name : ");
	scanf_s(" %[^\n]s", creatorNameInput, sizeof(creatorNameInput));

	noteMap.creatorName = creatorNameInput;

	system("cls");

	noteMap.noteData = tempNoteData;

	while (1)
	{
		ShowNoteMapData(bpm, noteDropSpeed, noteCount);

		switch (Input())
		{
		case 224:
			switch (_getch())
			{
			case 72:
				noteDropSpeed += noteDropSpeed + 1 <= 9999 ? 1 : 0;

				break;
			case 75:
				bpm -= bpm - 1 >= 0 ? 1 : 0;

				break;
			case 77:
				bpm += bpm + 1 <= 9999 ? 1 : 0;

				break;
			case 80:
				noteDropSpeed -= noteDropSpeed - 1 >= 0 ? 1 : 0;

				break;
			}

			break;
		case 77:
		case 109:
			noteCount += noteCount + 1 <= 10000 ? 1 : 0;

			break;
		case 68:
		case 100:
			noteCount -= noteCount - 1 >= 0 ? 1 : 0;

			break;
		case 83:
		case 115:
			sprintf_s(tempNoteData, sizeof(tempNoteData), "%d|%d|%d", bpm, noteDropSpeed, noteCount);
			SaveNoteMap(path, &noteMap);

			break;
		case 81:
		case 113:
			free(path);

			return 0;
		}
	}
}

void ShowNoteMapData(short bpm, short noteDropSpeed, short noteCount)
{
	Gotoxy(4, 2);
	printf("BPM (ก็, กๆ) : %04d", bpm);
	Gotoxy(4, 3);
	printf("Note Drop Speed (ก่, ก้) : %04d", noteDropSpeed);
	Gotoxy(4, 4);
	printf("Note Count (M, D) : %04d", noteCount);
	Gotoxy(4, 6);
	printf("M : Add Note");
	Gotoxy(4, 7);
	printf("D : Delete Note");
	Gotoxy(4, 8);
	printf("S : Save");
	Gotoxy(4, 9);
	printf("Q : Quit");
}