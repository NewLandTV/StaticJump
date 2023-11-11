#ifndef __NOTE_MAP_H__
#define __NOTE_MAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "System.h"
#include "Type.h"

#define NOTE_MAP_FOLDER_PATH "C:/NewLand/StaticJump/NoteMap/"

#pragma pack(push, 1)

typedef struct _NoteMap
{
	char* name;
	char* musicFilePath;
	char* composerName;
	char* creatorName;
	char* noteData;
} NoteMap;

#pragma pack(pop)

void CheckNoteMapFolder();
void SaveNoteMap(char* fileName, NoteMap noteMap);
NoteMap LoadNoteMap(char* fileName);
void ShowNoteMapInfo(char* fileName);

#endif
