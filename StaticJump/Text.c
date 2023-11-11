#include "Text.h"

void NDrawText(const Text* text)
{
	Gotoxy(text->position.x, text->position.y);
	printf("%s", text->value);
}