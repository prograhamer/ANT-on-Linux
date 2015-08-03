#include "ant_protocol.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int ANT_SendMessage(int fd, uchar type, const uchar const *data, const uchar data_length)
{
	uchar message[255];
	uchar checksum = 0;
	size_t length = data_length + 4;

	memset(message, 0, sizeof(message));

	message[0] = SYNC;
	message[1] = data_length;
	message[2] = type;
	memcpy(&message[3], data, (size_t) data_length);

	for(int i = 0; i < length - 1; i++)
		checksum ^= message[i];

	message[length - 1] = checksum;

	ANT_DebugHex(message, length);

	if(0 > write(fd, message, length))
	{
		perror("write");
		return -1;
	}

	return 0;
}

int ANT_SetNetworkKey(int fd, const uchar network_no, const uchar const *network_key)
{
	uchar write_buffer[9];

	write_buffer[0] = network_no;
	memcpy(&write_buffer[1], network_key, 8);
	return ANT_SendMessage(fd, SET_NETWORK_KEY, write_buffer, 9);
}

int ANT_AssignChannel(
		int fd,
		const uchar channel_no,
		const channel_type_t channel_type,
		const uchar network_no,
		const extended_assignment_t options)
{
	uchar write_buffer[4];

	write_buffer[0] = channel_no;
	write_buffer[1] = channel_type;
	write_buffer[2] = network_no;
	write_buffer[3] = options;
	return ANT_SendMessage(fd, ASSIGN_CHANNEL, write_buffer, 4);
}
