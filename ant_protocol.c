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

	ANT_DebugHex(message, length, 0);

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

int ANT_UnassignChannel(
		int fd,
		const uchar channel_no)
{
	uchar write_buffer[1];

	write_buffer[0] = channel_no;

	return ANT_SendMessage(fd, UNASSIGN_CHANNEL, write_buffer, 1);
}

int ANT_SetChannelID(
		int fd,
		const uchar channel_no,
		const ushort device_no,
		const uchar pairing_request,
		const uchar device_type,
		const uchar transmission_type)
{
	uchar write_buffer[5];
	
	write_buffer[0] = channel_no;
	write_buffer[1] = device_no & 0xFF;
	write_buffer[2] = (device_no >> 8) & 0xFF;
	write_buffer[3] = ((pairing_request & 0x01) << 7) | (device_type & 0x7F);
	write_buffer[4] = transmission_type;
	return  ANT_SendMessage(fd, SET_CHANNEL_ID, write_buffer, 5);
}

int ANT_SetRFFrequency(
		int fd,
		const uchar channel_no,
		const uchar rf_frequency)
{
	uchar write_buffer[2];

	write_buffer[0] = channel_no;
	write_buffer[1] = rf_frequency;
	return ANT_SendMessage(fd, SET_RF_FREQUENCY, write_buffer, 2);
}

int ANT_SetChannelPeriod(
		int fd,
		const uchar channel_no,
		const ushort period)
{
	uchar write_buffer[3];

	write_buffer[0] = channel_no;
	write_buffer[1] = period & 0xFF;
	write_buffer[2] = (period >> 8) & 0xFF;
	return ANT_SendMessage(fd, SET_CHANNEL_PERIOD, write_buffer, 3);
}

int ANT_OpenChannel(
		int fd,
		const uchar channel_no)
{
	uchar write_buffer[1];

	write_buffer[0] = channel_no;
	return ANT_SendMessage(fd, OPEN_CHANNEL, write_buffer, 1);
}

int ANT_CloseChannel(
		int fd,
		const uchar channel_no)
{
	uchar write_buffer[1];

	write_buffer[0] = channel_no;
	return ANT_SendMessage(fd, CLOSE_CHANNEL, write_buffer, 1);
}

int ANT_OpenRXScanMode(
		int fd)
{
	uchar write_buffer[1];

	write_buffer[0] = 0;
	return ANT_SendMessage(fd, OPEN_RX_SCAN_MODE, write_buffer, 1);
}

int ANT_RequestMessage(
		int fd,
		const uchar channel_no,
		const uchar message_id)
{
	uchar write_buffer[2];

	write_buffer[0] = channel_no;
	write_buffer[1] = message_id;

	return ANT_SendMessage(fd, REQUEST_MESSAGE, write_buffer, 2);
}
