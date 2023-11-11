#ifndef __NOTE_MAP_EDITOR_H__
#define __NOTE_MAP_EDITOR_H__

#include <stdio.h>
#include "System.h"
#include "NoteMap.h"

#define NOTE_MAP_FILE_EXTENSION ".sjnotmp"

void Setup();
void NoteMapEditor();
void ShowNoteMapData(short bpm, short noteDropSpeed, short noteCount);

#endif