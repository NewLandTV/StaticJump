#ifndef __TEXT_H__
#define __TEXT_H__

#include "Vector2.h"

typedef struct _Text
{
	Vector2 position;
	char* value;
} Text;

void NDrawText(const Text* text);

#endif