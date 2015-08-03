#include "types.h"
#include "debug.h"
#include "ant_serial.h"

#ifndef __ANT_PROTOCOL_H_
#define __ANT_PROTOCOL_H_

// Definitions

#define SYNC (0xA4)
#define SET_NETWORK_KEY (0x46)
#define ASSIGN_CHANNEL (0x42)

// Forward declarations

extern int ANT_SendMessage(
		int fd,
		uchar type,
		const uchar const *data,
		const uchar data_length
);

extern int ANT_SetNetworkKey(
		int fd,
		const uchar network_no,
		const uchar const *network_key
);

extern int ANT_AssignChannel(
		int fd,
		const uchar channel_no,
		const channel_type_t channel_type,
		const uchar network_no,
		const extended_assignment_t options
);

#endif // __ANT_PROTOCOL_H_
