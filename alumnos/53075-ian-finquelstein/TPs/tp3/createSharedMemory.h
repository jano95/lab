#ifndef _createSharedMemory_h_
#define _createSharedMemory_h_

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

char *create_shared_memory(size_t size);

#endif
