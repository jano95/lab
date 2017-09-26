CC = gcc
CFLAGS = -g -Wall
TARGETS = main

all: $(TARGETS)

main: main.c getopt.c create_server.c
	$(CC) $(CFLAGS) -o $@ main.c getopt.c create_server.c