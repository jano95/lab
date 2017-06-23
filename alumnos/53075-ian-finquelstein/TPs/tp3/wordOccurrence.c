#include "wordOccurrence.h"

void word_Occurrence(char *ptr)
{
  //Cadena en donde buscar ciertas palabras
  const char *haystack = ptr;
  //Palabra/as a buscar en la cadena
  const char *needle[] = {"de", "la", "kirchner"};
  for (int i = 0; i < ((int)( sizeof(needle) / sizeof(needle[0]))); i++) {
    unsigned total = 0;
    const char *p = haystack;
    while ( (p=strstr(p,needle[i])) != NULL ) {
            //encontrada la palabra posiciono el puntero
            //en el final de la misma para que continue buscando
            //de lo contrario strstr termina
            p += strlen(needle[i]);
            total++;
    }
    printf("%u ocurrencias de la palabra '%s'\n", total, needle[i]);
  }

}
