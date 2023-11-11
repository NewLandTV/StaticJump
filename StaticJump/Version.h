#ifndef __VERSION_H__
#define __VERSION_H__

#include <stdbool.h>

typedef struct _Version
{
	int major;
	int minor;
	int patch;
} Version;

bool CheckVersionDifferent(Version a, Version b);

#endif