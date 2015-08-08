#include "ant_serial.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <termios.h>
#include <string.h>

int ANT_SetSerialAttrs(int fd, int baud, int parity)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);

	if(tcgetattr(fd, &tty) != 0)
	{
		perror("tcgetattr");
		return -1;
	}

	// Set baud
	cfsetospeed(&tty, baud);
	cfsetispeed(&tty, baud);

	// 8-bit chars
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;

	// disable IGNBRK for mismatched baud tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;
	tty.c_lflag = 0;
	tty.c_oflag = 0;

	// Non-blocking read, timeout 500ms
	tty.c_cc[VMIN] = 0;
	tty.c_cc[VTIME] = 5;

	// Ignore modem controls
	tty.c_cflag |= (CLOCAL | CREAD);

	// No parity
	tty.c_cflag &= ~(PARENB | PARODD);

	tty.c_cflag |= parity;

	// No stop bits, flow control
	tty.c_cflag &= ~CSTOPB;

	if(tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		perror("tcsetattr");
		return -1;
	}

	return 0;
}

int ANT_OpenSerial(const char *path)
{
	int fd;

	fd = open(path, O_RDWR | O_NOCTTY | O_SYNC | O_EXCL);

	if(-1 == fd) return -1;

	if(-1 == ANT_SetSerialAttrs(fd, B115200, 0))
	{
		return -1;
	}

	return fd;
}
