#include "debug.h"
#include "ant_protocol.h"

#include <stdio.h>

void ANT_DebugHex(const uchar const *data, int length, uchar input)
{
	for(int i = 0; i < length; i++)
	{
		if(SYNC == data[i])
		{
			printf("\n");
			if(input) printf("\t<=");
			else printf("=>");
		}
		printf(" %02x", data[i]);
	}
}

