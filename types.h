#ifndef __ANT_TYPES_H_
#define __ANT_TYPES_H_

enum channel_type_t {
	ANT_RX_CHANNEL = 0x00,
	ANT_TX_CHANNEL = 0x10,
	ANT_SHARED_RX_CHANNEL = 0x20,
	ANT_SHARED_TX_CHANNEL = 0x30,
	ANT_RX_ONLY_CHANNEL = 0x40,
	ANT_TX_ONLY_CHANNEL = 0x50
};
typedef unsigned char channel_type_t;

enum extended_assignment_t {
	ANT_BACKGROUND_SCANNING = 0x01,
	ANT_FREQ_AGILITY = 0x04,
	ANT_FAST_CHANNEL_INIT = 0x10,
	ANT_ASYNC_TX = 0x20,
};
typedef unsigned char extended_assignment_t;

typedef unsigned char uchar;
typedef unsigned short ushort;

#endif // __ANT_TYPES_H_
