#include "debug.h"

#include <stdio.h>

void ANT_DebugHex(const uchar const *data, int length)
{
	for(int i = 0; i < length; i++)
		printf("<%02x>", data[i]);

	printf("\n");
}

