#include "ant.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

const uchar NETWORK_KEY[8] = {0, 0, 0, 0, 0, 0, 0, 0};

static __sig_atomic_t do_exit = 0;

void clean_exit(int signo)
{
	if(SIGINT == signo) do_exit = 1;
}

void read_response(int fd)
{
	uchar read_buffer[8192];

	int n = read(fd, read_buffer, sizeof(read_buffer));

	if(n < 0)
	{
		if(EINTR != errno)
		{
			perror("read");
			exit(1);
		}
	} else if (n > 0) {
		ANT_DebugHex(read_buffer, n, 1);
	}
}

void read_loop(int fd)
{
	while(!do_exit) {
		read_response(fd);
		sleep(1);
	}

	printf("\nExiting...\n");
}

int main(int argc, char *argv[])
{
	if(SIG_ERR == signal(SIGINT, clean_exit))
	{
		perror("signal");
		exit(1);
	}

	int fd = ANT_OpenSerial("/dev/ttyUSB0");

	if(-1 == fd)
	{
		perror("Failed to open serial connection");
		exit(1);
	}

	ANT_SetNetworkKey(fd, 0, NETWORK_KEY);
	read_response(fd);

	ANT_AssignChannel(fd, 0, ANT_RX_CHANNEL, 0, 0);
	read_response(fd);

	ANT_SetChannelID(fd, 0, 0, 0, 0x78, 0);
	read_response(fd);

	ANT_SetRFFrequency(fd, 0, ANT_PLUS_FREQUENCY);
	read_response(fd);

	ANT_SetChannelPeriod(fd, 0, ANT_PLUS_PERIOD_102);
	read_response(fd);

	ANT_OpenRXScanMode(fd);
	read_response(fd);

	read_loop(fd);

	ANT_RequestMessage(fd, 0, SET_CHANNEL_ID);

	do_exit = 0;
	read_loop(fd);

  //ANT_UnassignChannel(fd, 0);
	//read_response(fd);

  ANT_CloseChannel(fd, 0);
	read_response(fd);

	close(fd);
	return 0;
}
