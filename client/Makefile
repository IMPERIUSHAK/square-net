CC = gcc
CFLAGS = -Wall -g -Iinclude $(shell sdl2-config --cflags) -I../shared
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf
SRCS = src/main.c src/window.c src/loop.c src/event_handler.c src/user.c src/net_client.c
TARGET = main

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean