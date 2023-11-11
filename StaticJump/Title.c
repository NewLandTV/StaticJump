#include "Title.h"

void DrawTitle(const Version* mainVersion)
{
	Button gameButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) - 27, CONSOLE_HEIGHT - 19 }, (Vector2) { 20, 5 }, "PLAY", ' '
	};
	Button noteMapEditorButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) + 7, CONSOLE_HEIGHT - 19 }, (Vector2) { 19, 5 }, "NOTE MAP EDITOR", ' '
	};
	Button settingButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) - 16, CONSOLE_HEIGHT - 10 }, (Vector2) { 13, 3  }, "SETTING", ' '
	};
	Button quitButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) + 3, CONSOLE_HEIGHT - 10 }, (Vector2) { 12, 3 }, "QUIT", ' '
	};

	char versionTextValue[32];

	sprintf_s(versionTextValue, 32, "v%d.%d.%d", mainVersion->major, mainVersion->minor, mainVersion->patch);

	Text versionText =
	{
		(Vector2) { 2, CONSOLE_HEIGHT - 2 }, versionTextValue
	};

	NoteMap noteMap;

	memset(&noteMap, 0, sizeof(NoteMap));

	DrawButton(&gameButton);
	DrawButton(&noteMapEditorButton);
	DrawButton(&settingButton);
	DrawButton(&quitButton);
	NDrawText(&versionText);

	while (1)
	{
		if (CheckClick(&gameButton))
		{
			system("cls");
			Title(&noteMap);
			Start(&noteMap);
			Update();
			system("cls");
			DrawButton(&gameButton);
			DrawButton(&noteMapEditorButton);
			DrawButton(&settingButton);
			DrawButton(&quitButton);
			NDrawText(&versionText);
		}

		if (CheckClick(&noteMapEditorButton))
		{
			system("cls");
			Setup();
			NoteMapEditor();
			system("cls");
			DrawButton(&gameButton);
			DrawButton(&noteMapEditorButton);
			DrawButton(&settingButton);
			DrawButton(&quitButton);
			NDrawText(&versionText);
		}

		if (CheckClick(&settingButton))
		{
			system("cls");
			DrawSetting();
			system("cls");
			DrawButton(&gameButton);
			DrawButton(&noteMapEditorButton);
			DrawButton(&settingButton);
			DrawButton(&quitButton);
			NDrawText(&versionText);
		}

		if (CheckClick(&quitButton))
		{
			system("cls");

			return 0;
		}
	}
}

void DrawSetting()
{
	Button confirmButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) - 5, CONSOLE_HEIGHT - 5 }, (Vector2) { 11, 3 }, "CONFIRM", ' '
	};
	Button englishButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) - 15, 7 }, (Vector2) { 13, 7 }, "ENGLISH", ' '
	};
	Button koreaButton =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) + 5, 7 }, (Vector2) { 13, 7 }, "KOREA", ' '
	};

	Text languageText =
	{
		(Vector2) { (CONSOLE_WIDTH >> 1) - 3, 3 }, "LANGUAGE"
	};

	DrawBoard(&(Vector2) { 1, 1 }, &(Vector2) { CONSOLE_WIDTH - 1, CONSOLE_HEIGHT - 16 });
	DrawButton(&confirmButton);
	DrawButton(&englishButton);
	DrawButton(&koreaButton);
	NDrawText(&languageText);

	while (1)
	{
		if (CheckClick(&confirmButton))
		{
			return;
		}

		if (CheckClick(&englishButton))
		{
			// TODO english

			break;
		}

		if (CheckClick(&koreaButton))
		{
			// TODO ÇÑ±¹¾î

			break;
		}
	}
}

void Title(NoteMap* outNoteMap)
{
	// "test", "C:\\NewLand\\StaticJump\\NoteMap\\test.mp3", "NewLand Melodic Artist", "JkhTV", "80|30|60"

	LoadNoteMap("test.sjnotmp", outNoteMap);
	ShowNoteMapInfo(outNoteMap);
	Gotoxy((CONSOLE_WIDTH >> 1) - 7, 5);
	printf("PRESS ANY KEY");

	while (!_kbhit());

	system("cls");
}