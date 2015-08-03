#include "ant.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

const uchar NETWORK_KEY[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void read_response(int fd)
{
	uchar read_buffer[256];

	int n = read(fd, read_buffer, sizeof(read_buffer));

	if(n < 0)
	{
		perror("read");
		exit(1);
	} else if (n > 0) {
		ANT_DebugHex(read_buffer, n);
	} else {
		printf("NO DATA READ!\n");
	}
}

int main(int argc, char *argv[])
{
	int fd = ANT_OpenSerial("/dev/ttyUSB0");

	if(-1 == fd)
	{
		perror("Failed to open serial connection");
		exit(1);
	}

	ANT_SetNetworkKey(fd, 0x01, NETWORK_KEY);

	read_response(fd);

	ANT_AssignChannel(fd, 0x0, ANT_RX_CHANNEL, 0x01, ANT_BACKGROUND_SCANNING);

	read_response(fd);

	close(fd);
	return 0;
}
