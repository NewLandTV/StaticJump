#include "NoteMap.h"

FILE* fp;

void CheckNoteMapFolder()
{
	char buffer[1024];
	char* dir = buffer;
	
	strcpy(buffer, NOTE_MAP_FOLDER_PATH);
	
	buffer[1023] = '\0';
	
	while (*dir)
	{
		if (*dir == '/')
		{
			*dir = '\0';
			
			mkdir(buffer);
			
			*dir = '/';
		}
		
		dir++;
	}
}

void SaveNoteMap(char* fileName, NoteMap noteMap)
{
	CheckNoteMapFolder();
	
	char* path = (char*)malloc(sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName)));
	
	strcpy(path, NOTE_MAP_FOLDER_PATH);
	strcat(path, fileName);
	
	fp = fopen(path, "wb");
	
	free(path);
	fwrite(&noteMap, sizeof(noteMap), 1, fp);
	fclose(fp);
}

NoteMap LoadNoteMap(char* fileName)
{
	NoteMap noteMap;
	
	char* path = (char*)malloc(sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName)));
	
	strcpy(path, NOTE_MAP_FOLDER_PATH);
	strcat(path, fileName);
	
	fp = fopen(path, "rb");
	
	free(path);
	
	if (fp == NULL)
	{
		return noteMap;
	}
	
	fread(&noteMap, sizeof(noteMap), 1, fp);
	fclose(fp);
	
	return noteMap;
}

void ShowNoteMapInfo(char* fileName)
{
	NoteMap noteMap = LoadNoteMap(fileName);
	
	system("cls");
	
	Gotoxy(5, CONSOLE_HEIGHT - 6);
	
	printf("Name : %s", noteMap.name);
	
	Gotoxy(5, CONSOLE_HEIGHT - 5);
	
	printf("Composer Name : %s", noteMap.composerName);
	
	Gotoxy(5, CONSOLE_HEIGHT - 4);
	
	printf("Creator Name : %s", noteMap.creatorName);
	
	// TODO play the music of selected.
}
