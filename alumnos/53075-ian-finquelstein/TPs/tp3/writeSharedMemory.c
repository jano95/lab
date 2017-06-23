#include "writeSharedMemory.h"

void write_shared_memory(char *input_filename, char *shm)
{
  int nread;
  int fd;
  char buffer[1500];
  fd = open(input_filename, O_RDONLY, 0666);

  do {
      // memset(buffer, 0, sizeof buffer);
      nread = read(fd, buffer, sizeof buffer);
      for (int i = 0 ; i < sizeof buffer ; i++){
        *(shm+i) = *(buffer+i);
      }
  } while (nread > 0);
}
