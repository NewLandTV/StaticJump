#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "System.h"
#include "Sound.h"
#include "Note.h"
#include "NoteMap.h"
#include "Button.h"
#include "Vector2.h"

typedef enum _JUDGE_RESULT
{
	PERFECT,
	GREAT,
	GOOD,
	BAD,
	MISS
} JUDGE_RESULT;

void Start(NoteMap* noteMap);
void Update();
void End();
void Pause();
void DrawNote(const Note* note);
void ClearNote(const Note* note);
void DrawHitLine();
void DrawHitKey();
void DrawCombo();
void DrawScore();
void DrawLine();
void DrawJudge();
void DropNote();
int HitNote(int randomPositionX);
JUDGE_RESULT JudgeNote(const Note* note);

#endif