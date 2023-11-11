#include "System.h"
#include "Title.h"
#include "Game.h"
#include "Version.h"
#include "NoteMap.h"
#include "NoteMapEditor.h"

int main(int argc, char** argv)
{
	Version mainVersion =
	{
		1, 0, 0
	};

	NoteMap noteMap;

	memset(&noteMap, 0, sizeof(NoteMap));

	Init();

	if (argc == 2)
	{
		if (!strcmp(argv[1], "GAME"))
		{
			Title(&noteMap);
			Start(&noteMap);
			Update();
		}
		if (!strcmp(argv[1], "NOTE_MAP_EDITOR"))
		{
			Setup();
			NoteMapEditor();
		}
		if (!strcmp(argv[1], "SETTING"))
		{
			system("cls");
			DrawSetting();
		}

		system("cls");
		DrawTitle(&mainVersion);
	}
	else
	{
		DrawTitle(&mainVersion);
	}

	return 0;
}