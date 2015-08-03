CC=gcc
CFLAGS=-std=c11 -g -O2
LDFLAGS=
SOURCES=ant_serial.c ant_protocol.c debug.c ant.c
DEPENDS=$(SOURCES:.c=.d)
OBJECTS=$(SOURCES:.c=.o)
TARGET=ant

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) -MMD -o $@ $<

-include $(DEPENDS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS)

.PHONY: tags
tags:
	ctags *.c *.h
