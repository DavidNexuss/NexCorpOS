#include "stdafx.h"
#include "runtime/string.h"

char* strcpy(char* destination, const char* source)
{
	if (destination == 0)
		return 0;
	char *ptr = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return ptr;
}
