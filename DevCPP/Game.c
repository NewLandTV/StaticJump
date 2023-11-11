#include "System.h"
#include "Game.h"

USHORT bpm;
USHORT noteDropSpeed;
USHORT noteCount;
USHORT hitKey;
UINT score;

void SetNoteMap(NoteMap noteMap)
{
	int i;
	char tempNoteData[15];
	char* ptr;
	
	strcpy(tempNoteData, noteMap.noteData);
	
	ptr = strtok(tempNoteData, "|");
	
	for (i = 0; ptr != NULL; i++)
	{
		if (i == 0)
		{
			bpm = atoi(ptr);
		}
		if (i == 1)
		{
			noteDropSpeed = atoi(ptr);
		}
		if (i == 2)
		{
			noteCount = atoi(ptr);
		}
		
		ptr = strtok(NULL, "|");
	}
}

void Update()
{
	int i = 0;
	
	for (i = 0; i < noteCount; i++)
	{
		DropNote();
		
		Sleep(1000 / bpm);
	}
}

void DrawNote(Note note)
{
	int noteX;
	int noteY;
	
	for (noteY = note.position.y; noteY < note.position.y + note.scale.y; noteY++)
	{
		for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
		{
			Gotoxy(noteX, noteY);
			
			printf("%c", note.sprite);
		}
	}
}

void DrawScore()
{
	Gotoxy(CONSOLE_WIDTH - 10, 1);
	
	printf("%09d", score);
}

void DrawLine()
{
	int i;
	int y;
	
	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		for (i = 0; i < 3; i++)
		{
			Gotoxy(i * (CONSOLE_WIDTH / 4 - 1) + CONSOLE_WIDTH / 4 - 3, y);
			
			printf("+");
		}
	}
}

void DropNote()
{
	int y;
	int noteX;
	int noteY;
	
	Note note;
	
	note.position.x = rand() % 4 * (CONSOLE_WIDTH / 4 - 1);
	note.position.y = 0;
	note.scale.x = CONSOLE_WIDTH / 4 - 4;
	note.scale.y = 2;
	note.sprite = '#';
	
	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		DrawScore();
		DrawLine();
		
		switch (Input())
		{
			case 32:
				hitKey = 1;
				
				break;
		}
		
		if (HitNote())
		{
			switch (JudgeNote(note))
			{
				case PERFECT:
					score += 100;
					
					for (noteY = note.position.y; noteY < note.position.y + note.scale.y; noteY++)
					{
						for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
						{
							Gotoxy(noteX, noteY);
							
							printf(" ");
						}
					}
					
					return;
				case GREAT:
					score += 75;
					
					for (noteY = note.position.y; noteY < note.position.y + note.scale.y; noteY++)
					{
						for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
						{
							Gotoxy(noteX, noteY);
							
							printf(" ");
						}
					}
					
					return;
				case GOOD:
					score += 40;
					
					for (noteY = note.position.y; noteY < note.position.y + note.scale.y; noteY++)
					{
						for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
						{
							Gotoxy(noteX, noteY);
							
							printf(" ");
						}
					}
					
					return;
				case BAD:
					score += 5;
					
					for (noteY = note.position.y; noteY < note.position.y + note.scale.y; noteY++)
					{
						for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
						{
							Gotoxy(noteX, noteY);
							
							printf(" ");
						}
					}
					
					return;
			}
		}
		
		DrawNote(note);
		
		note.position.y = y;
		
		Sleep(1000 / noteDropSpeed);
		
		for (noteY = note.position.y - note.scale.y; noteY < note.position.y + 1; noteY++)
		{
			for (noteX = note.position.x; noteX < note.position.x + note.scale.x; noteX++)
			{
				Gotoxy(noteX, noteY);
				
				printf(" ");
			}
		}
	}
}

int HitNote()
{
	if (hitKey)
	{
		hitKey = 0;
		
		return 1;
	}
	
	return 0;
}

JUDGE_RESULT JudgeNote(Note note)
{
	if (CONSOLE_HEIGHT - 10 <= note.position.y && note.position.y <= CONSOLE_HEIGHT - 8)
	{
		return PERFECT;
	}
	if (CONSOLE_HEIGHT - 12 <= note.position.y && note.position.y <= CONSOLE_HEIGHT - 6)
	{
		return GREAT;
	}
	if (CONSOLE_HEIGHT - 15 <= note.position.y && note.position.y <= CONSOLE_HEIGHT - 3)
	{
		return GOOD;
	}
	if (CONSOLE_HEIGHT - 19 <= note.position.y && note.position.y <= CONSOLE_HEIGHT)
	{
		return BAD;
	}
	
	return MISS;
}
