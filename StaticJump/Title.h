#ifndef __TITLE_H__
#define __TITLE_H__

#include <conio.h>
#include <stdlib.h>
#include "System.h"
#include "Game.h"
#include "NoteMap.h"
#include "NoteMapEditor.h"
#include "Board.h"
#include "Button.h"
#include "Text.h"
#include "Version.h"
#include "Vector2.h"

void DrawTitle(const Version* mainVersion);
void DrawSetting();
void Title(NoteMap* outNoteMap);

#endif