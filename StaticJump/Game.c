#include "Game.h"

NoteMap* currentNoteMap;

short bpm;
short noteDropSpeed;
short noteCount;
int score;
int combo;
bool hitKey[4];

JUDGE_RESULT judgeResult;

void Start(NoteMap* noteMap)
{
	RePlayMusic(false);

	currentNoteMap = noteMap;

	int i;
	char* ptr;
	char* context = NULL;

	ptr = strtok_s(currentNoteMap->noteData, "|", &context);

	bpm = atoi(ptr);
	ptr = strtok_s(NULL, "|", &context);
	noteDropSpeed = atoi(ptr);
	ptr = strtok_s(NULL, "|", &context);
	noteCount = atoi(ptr);
}

void Update()
{
	int i;

	for (i = 0; i < noteCount; i++)
	{
		DropNote();
		Delay(1000 / bpm);
	}

	End();
}

void End()
{
	free(currentNoteMap->name);
	free(currentNoteMap->musicFilePath);
	free(currentNoteMap->composerName);
	free(currentNoteMap->creatorName);
	free(currentNoteMap->noteData);
}

void Pause()
{
	PauseMusic();

	Vector2 unPauseButtonPosition =
	{
		(CONSOLE_WIDTH >> 1) - 5, (CONSOLE_HEIGHT >> 1) - 5
	};

	Vector2 unPauseButtonScale =
	{
		11, 5
	};

	Button unPauseButton =
	{
		unPauseButtonPosition, unPauseButtonScale, "UNPAUSE", ' '
	};

	DrawButton(&unPauseButton);

	while (!CheckClick(&unPauseButton));

	system("cls");
	UnpauseMusic();
}

void DrawNote(const Note* note)
{
	int noteX;
	int noteY;

	for (noteY = note->position.y; noteY < note->position.y + note->scale.y; noteY++)
	{
		for (noteX = note->position.x; noteX < note->position.x + note->scale.x; noteX++)
		{
			Gotoxy(noteX, noteY);
			printf("%c", note->sprite);
		}
	}
}

void ClearNote(const Note* note)
{
	int noteX;
	int noteY;

	for (noteY = note->position.y; noteY < note->position.y + note->scale.y; noteY++)
	{
		for (noteX = note->position.x; noteX < note->position.x + note->scale.x; noteX++)
		{
			Gotoxy(noteX, noteY);
			printf(" ");
		}
	}
}

void DrawHitLine()
{
	int x;

	for (x = 0; x < 3 * ((CONSOLE_WIDTH >> 2) - 5) + (CONSOLE_WIDTH >> 2) - 7; x++)
	{
		Gotoxy(x, CONSOLE_HEIGHT - 9);
		printf("~");
	}
}

void DrawHitKey()
{
	Gotoxy(0 * ((CONSOLE_WIDTH >> 2) - 5) + (((CONSOLE_WIDTH >> 2) - 8) >> 1), CONSOLE_HEIGHT - 4);
	printf("F");
	Gotoxy(1 * ((CONSOLE_WIDTH >> 2) - 5) + (((CONSOLE_WIDTH >> 2) - 8) >> 1), CONSOLE_HEIGHT - 4);
	printf("G");
	Gotoxy(2 * ((CONSOLE_WIDTH >> 2) - 5) + (((CONSOLE_WIDTH >> 2) - 8) >> 1), CONSOLE_HEIGHT - 4);
	printf("H");
	Gotoxy(3 * ((CONSOLE_WIDTH >> 2) - 5) + (((CONSOLE_WIDTH >> 2) - 8) >> 1), CONSOLE_HEIGHT - 4);
	printf("J");
}

void DrawCombo()
{
	Gotoxy(CONSOLE_WIDTH - 19, 3);
	printf("COMBO : %09d", combo);
}

void DrawScore()
{
	Gotoxy(CONSOLE_WIDTH - 19, 1);
	printf("SCORE : %09d", score);
}

void DrawLine()
{
	int i;
	int y;

	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		for (i = 0; y != CONSOLE_HEIGHT - 9 && i < 3; i++)
		{
			Gotoxy(i * ((CONSOLE_WIDTH >> 2) - 5) + (CONSOLE_WIDTH >> 2) - 7, y);
			printf("+");
		}
	}
}

void DrawJudge()
{
	Gotoxy(CONSOLE_WIDTH - 13, 5);
	printf("[");

	switch (judgeResult)
	{
	case PERFECT:
		printf("PERFECT");

		break;
	case GREAT:
		printf(" GREAT ");

		break;
	case GOOD:
		printf(" GOOD  ");

		break;
	case BAD:
		printf("  BAD  ");

		break;
	case MISS:
		printf(" MISS  ");

		break;
	}

	printf("]");
}

void DropNote()
{
	int y;
	int noteX;
	int noteY;
	int randomPositionX = rand() % 4;

	Note note;

	note.position.x = randomPositionX * ((CONSOLE_WIDTH >> 2) - 5);
	note.position.y = 0;
	note.scale.x = (CONSOLE_WIDTH >> 2) - 8;
	note.scale.y = 2;
	note.sprite = '#';

	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		DrawScore();
		DrawLine();

		switch (Input())
		{
		case 27:
			Pause();

			break;
		case 70:
		case 102:
			hitKey[0] = true;

			break;
		case 71:
		case 103:
			hitKey[1] = true;

			break;
		case 72:
		case 104:
			hitKey[2] = true;

			break;
		case 74:
		case 106:
			hitKey[3] = true;

			break;
		}

		if (HitNote(randomPositionX))
		{
			judgeResult = JudgeNote(&note);

			switch (judgeResult)
			{
			case PERFECT:
				score += 100 + 75 * combo;

				combo++;

				ClearNote(&note);

				return;
			case GREAT:
				score += 75;

				combo = 0;

				ClearNote(&note);

				return;
			case GOOD:
				score += 40;

				combo = 0;

				ClearNote(&note);

				return;
			case BAD:
				score += 5;

				combo = 0;

				ClearNote(&note);

				return;
			case MISS:
				combo = 0;

				break;
			}
		}

		DrawNote(&note);
		DrawHitLine();
		DrawHitKey();
		DrawCombo();
		DrawJudge();

		note.position.y = y;

		Gotoxy(0, 0);
		Delay(1000 / noteDropSpeed);

		for (noteY = note.position.y - note.scale.y; noteY < note.position.y + 1; noteY++)
		{
			for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
			{
				Gotoxy(noteX, noteY);
				printf(" ");
			}
		}
	}

	judgeResult = MISS;

	combo = 0;
}

int HitNote(int randomPositionX)
{
	if (hitKey[randomPositionX])
	{
		hitKey[randomPositionX] = false;

		return 1;
	}

	return 0;
}

JUDGE_RESULT JudgeNote(const Note* note)
{
	if (CONSOLE_HEIGHT - 10 <= note->position.y && note->position.y <= CONSOLE_HEIGHT - 8)
	{
		return PERFECT;
	}
	if (CONSOLE_HEIGHT - 12 <= note->position.y && note->position.y <= CONSOLE_HEIGHT - 6)
	{
		return GREAT;
	}
	if (CONSOLE_HEIGHT - 15 <= note->position.y && note->position.y <= CONSOLE_HEIGHT - 3)
	{
		return GOOD;
	}
	if (CONSOLE_HEIGHT - 19 <= note->position.y && note->position.y <= CONSOLE_HEIGHT)
	{
		return BAD;
	}

	return MISS;
}