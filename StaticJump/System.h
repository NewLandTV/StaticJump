#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define CONSOLE_WIDTH 140
#define CONSOLE_HEIGHT 55

void Init();
void Gotoxy(int x, int y);
int Input();
void Delay(clock_t waitTIme);

#endif