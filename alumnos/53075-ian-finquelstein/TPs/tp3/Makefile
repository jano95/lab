CC = gcc
CFLAGS = -g -Wall
TARGETS = main

all: $(TARGETS)

main: main.c process.c getopt.c createSharedMemory.c wordCount.c wordOccurrence.c writeSharedMemory.c fileSize.c
	$(CC) $(CFLAGS) -o $@ main.c process.c getopt.c createSharedMemory.c wordCount.c wordOccurrence.c writeSharedMemory.c fileSize.c
