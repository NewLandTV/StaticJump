#include "NoteMap.h"

void CheckNoteMapFolder()
{
	char buffer[1024];
	char* dir = buffer;

	strcpy_s(buffer, 1024, NOTE_MAP_FOLDER_PATH);

	buffer[1023] = '\0';

	while (*dir)
	{
		if (*dir == '/')
		{
			*dir = '\0';

			_mkdir(buffer);

			*dir = '/';
		}

		dir++;
	}
}

void SaveNoteMap(const char* fileName, const NoteMap* noteMap)
{
	FILE* fp = NULL;

	CheckNoteMapFolder();

	char* path = (char*)malloc((sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName))) + 1);

	if (path)
	{
		strcpy_s(path, (sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName))) + 1, NOTE_MAP_FOLDER_PATH);
		strcat_s(path, (sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName))) + 1, fileName);
		fopen_s(&fp, path, "wb");
	}

	free(path);

	if (fp)
	{
		size_t nameSize = strlen(noteMap->name) + 1;
		size_t musicFilePathSize = strlen(noteMap->musicFilePath) + 1;
		size_t composerNameSize = strlen(noteMap->composerName) + 1;
		size_t creatorNameSize = strlen(noteMap->creatorName) + 1;
		size_t noteDataSize = strlen(noteMap->noteData) + 1;

		fwrite(&nameSize, sizeof(size_t), 1, fp);
		fwrite(noteMap->name, sizeof(char), nameSize, fp);
		fwrite(&musicFilePathSize, sizeof(size_t), 1, fp);
		fwrite(noteMap->musicFilePath, sizeof(char), musicFilePathSize, fp);
		fwrite(&composerNameSize, sizeof(size_t), 1, fp);
		fwrite(noteMap->composerName, sizeof(char), composerNameSize, fp);
		fwrite(&creatorNameSize, sizeof(size_t), 1, fp);
		fwrite(noteMap->creatorName, sizeof(char), creatorNameSize, fp);
		fwrite(&noteDataSize, sizeof(size_t), 1, fp);
		fwrite(noteMap->noteData, sizeof(char), noteDataSize, fp);
		fclose(fp);
	}
}

void LoadNoteMap(const char* fileName, NoteMap* outNoteMap)
{
	FILE* fp = NULL;

	char* path = (char*)malloc((sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName))) + 1);

	if (path)
	{
		strcpy_s(path, (sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName))) + 1, NOTE_MAP_FOLDER_PATH);
		strcat_s(path, (sizeof(char) * (strlen(NOTE_MAP_FOLDER_PATH) + strlen(fileName))) + 1, fileName);
		fopen_s(&fp, path, "rb");
	}

	free(path);

	if (!fp)
	{
		outNoteMap = NULL;

		return;
	}

	size_t nameSize;
	size_t musicFilePathSize;
	size_t composerNameSize;
	size_t creatorNameSize;
	size_t noteDataSize;

	fread(&nameSize, sizeof(size_t), 1, fp);

	outNoteMap->name = (char*)malloc(nameSize);

	fread(outNoteMap->name, sizeof(char), nameSize, fp);
	fread(&musicFilePathSize, sizeof(size_t), 1, fp);

	outNoteMap->musicFilePath = (char*)malloc(musicFilePathSize);

	fread(outNoteMap->musicFilePath, sizeof(char), musicFilePathSize, fp);
	fread(&composerNameSize, sizeof(size_t), 1, fp);

	outNoteMap->composerName = (char*)malloc(composerNameSize);

	fread(outNoteMap->composerName, sizeof(char), composerNameSize, fp);
	fread(&creatorNameSize, sizeof(size_t), 1, fp);

	outNoteMap->creatorName = (char*)malloc(creatorNameSize);

	fread(outNoteMap->creatorName, sizeof(char), creatorNameSize, fp);
	fread(&noteDataSize, sizeof(size_t), 1, fp);

	outNoteMap->noteData = (char*)malloc(noteDataSize);

	fread(outNoteMap->noteData, sizeof(char), noteDataSize, fp);
	fclose(fp);
}

void ShowNoteMapInfo(const NoteMap* noteMap)
{
	system("cls");
	Gotoxy(5, CONSOLE_HEIGHT - 6);
	printf("Name : %s", noteMap->name);
	Gotoxy(5, CONSOLE_HEIGHT - 5);
	printf("Composer Name : %s", noteMap->composerName);
	Gotoxy(5, CONSOLE_HEIGHT - 4);
	printf("Creator Name : %s", noteMap->creatorName);
	PlayMusic(noteMap->musicFilePath, true);
}