#pragma once
#ifdef __cplusplus
extern "C"{
#endif
char* strcpy(char* destination, const char* source)
{
	// return if no memory is allocated to the destination
	if (destination == 0)
		return 0;

	// take a pointer pointing to the beginning of destination string
	char *ptr = destination;
	
	// copy the C-string pointed by source into the array
	// pointed by destination
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	// include the terminating null character
	*destination = '\0';

	// destination is returned by standard strcpy()
	return ptr;
}

#ifdef __cplusplus
}
#endif