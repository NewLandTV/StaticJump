#include "Version.h"

bool CheckVersionDifferent(Version a, Version b)
{
	return a.major != b.major && a.minor != b.minor && a.patch != b.patch;
}