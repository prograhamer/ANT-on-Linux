#include "types.h"
#include "debug.h"
#include "ant_serial.h"

#ifndef __ANT_PROTOCOL_H_
#define __ANT_PROTOCOL_H_

// Definitions

#define SYNC (0xA4) // SYNC byte that leads messages
#define ANT_PLUS_FREQUENCY (57)
#define ANT_PLUS_PERIOD_406 (8070)
#define ANT_PLUS_PERIOD_203 (16140)
#define ANT_PLUS_PERIOD_102 (32280)

// Message types
#define SET_NETWORK_KEY (0x46)
#define ASSIGN_CHANNEL (0x42)
#define UNASSIGN_CHANNEL (0x41)
#define SET_CHANNEL_ID (0x51)
#define CHANNEL_RESPONSE_EVENT (0x40)
#define SET_RF_FREQUENCY (0x45)
#define SET_CHANNEL_PERIOD (0x43)
#define OPEN_CHANNEL (0x48)
#define CLOSE_CHANNEL (0x4C)
#define OPEN_RX_SCAN_MODE (0x5B)
#define REQUEST_MESSAGE (0x4D)

// Forward declarations

extern int ANT_SendMessage(
		int fd,
		uchar type,
		const uchar *data,
		const uchar data_length
);

extern int ANT_SetNetworkKey(
		int fd,
		const uchar network_no,
		const uchar *network_key
);

extern int ANT_AssignChannel(
		int fd,
		const uchar channel_no,
		const channel_type_t channel_type,
		const uchar network_no,
		const extended_assignment_t options
);

extern int ANT_UnassignChannel(
		int fd,
		const uchar channel_no
);

extern int ANT_SetChannelID(
		int fd,
		const uchar channel_no,
		const ushort device_no,
		const uchar pairing_request,
		const uchar device_type,
		const uchar transmission_type
);

extern int ANT_SetRFFrequency(
		int fd,
		const uchar channel_no,
		const uchar rf_frequency
);

extern int ANT_SetChannelPeriod(
		int fd,
		const uchar channel_no,
		const ushort period
);

extern int ANT_OpenChannel(
		int fd,
		const uchar channel_no
);

extern int ANT_CloseChannel(
		int fd,
		const uchar channel_no
);

extern int ANT_OpenRXScanMode(
		int fd
);

extern int ANT_RequestMessage(
		int fd,
		const uchar channel_no,
		const uchar message_id
);

#endif // __ANT_PROTOCOL_H_
