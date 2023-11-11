#include "System.h"
#include "Title.h"
#include "Game.h"
#include "NoteMapEditor.h"
#include "Button.h"
#include "Vector2.h"

int main(int argc, char** argv)
{	
	Init();
	
	if (argc == 2)
	{
		if (strcmp(argv[1], "GAME") == 0)
		{
			SetNoteMap(Title());
			Update();
		}
		if (strcmp(argv[1], "NOTE_MAP_EDITOR") == 0)
		{
			Setup();
			NoteMapEditor();
		}
	}
	else
	{
		Vector2 gameButtonPosition =
		{
			CONSOLE_WIDTH / 2 - 26, 7
		};
		Vector2 gameButtonScale =
		{
			19, 3
		};
		Vector2 noteMapEditorButtonPosition =
		{
			CONSOLE_WIDTH / 2 + 7, 7
		};
		Vector2 noteMapEditorButtonScale =
		{
			19, 3
		};
		
		Button gameButton = 
		{
			gameButtonPosition, gameButtonScale, "GAME", '+'
		};
		Button noteMapEditorButton =
		{
			noteMapEditorButtonPosition, noteMapEditorButtonScale, "NOTE MAP EDITOR", '+'
		};
		
		DrawButton(gameButton);
		DrawButton(noteMapEditorButton);
		
		while (1)
		{
			if (CheckClick(gameButton))
			{
				SetNoteMap(Title());
				Update();
				
				return 0;
			}
			
			if (CheckClick(noteMapEditorButton))
			{
				Setup();
				NoteMapEditor();
				
				return 0;
			}
		}
	}
	
	return 0;
}
