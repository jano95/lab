#include "process.h"
#include "wordCount.h"
#include "wordOccurrence.h"

int launch_Process(int number_of_children, char *ptr)
{
  for(int i = 0; i < number_of_children; i++) {
    switch(fork()) {
      case 0:
      printf("Hijo%d(): %d\n", i,getpid());
      if (i != (number_of_children - 1)) {
        word_Count(ptr);
      }
      else {
        word_Occurrence(ptr);
      }
      return 0;

      case -1:
      perror("fork()");
      return -1;
    }
  }
  return 0;
}
