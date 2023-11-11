#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include "Note.h"
#include "NoteMap.h"
#include "Vector2.h"

typedef enum _JUDGE_RESULT
{
	PERFECT,
	GREAT,
	GOOD,
	BAD,
	MISS
} JUDGE_RESULT;

void SetNoteMap(NoteMap noteMap);
void Update();
void DrawNote(Note note);
void DrawScore();
void DrawLine();
void DropNote();
int HitNote();
JUDGE_RESULT JudgeNote(Note note);

#endif
