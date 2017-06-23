#include "wordCount.h"

void word_Count(char *ptr)
{
  char aux[1500];
  strcpy(aux,ptr);
  int counter = 0;
  char *tok;
  char *delim = " \t\n";
  for (tok = strtok(aux, delim);
    tok != NULL;
    tok = strtok(NULL, delim), counter++);
  printf("Cantidad de palabras: %d\n", counter);
}
