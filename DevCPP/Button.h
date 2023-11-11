#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "System.h"
#include "Math.h"
#include "Vector2.h"
#include "Type.h"

typedef struct _Button
{
	Vector2 position;
	Vector2 scale;
	char* text;
	char backgroundSprite;
} Button;

void DrawButton(Button button);
USHORT CheckClick(Button button);

#endif
