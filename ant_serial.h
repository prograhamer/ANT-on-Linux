#include "types.h"
#include "debug.h"

#ifndef __ANT_SERIAL_H_
#define __ANT_SERIAL_H_

extern int ANT_SetSerialAttrs(
		int fd,
		int baud,
		int parity
);

extern int ANT_OpenSerial(
		const char const *path
);

#endif // __ANT_SERIAL_H_
