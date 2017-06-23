#include "createSharedMemory.h"

char *create_shared_memory(size_t size)
{
  // El buffer de memoria va a ser leido y escrito
  int protection = PROT_READ | PROT_WRITE;

  // El buffer va a ser compartido
  // pero anonimo para que procesos no relacionado no puedan acceder
  // para que este proceso y sus hijos puedan acceder unicamente
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // Devuelvo el puntero a memoria compartida
  return mmap(NULL, size, protection, visibility, 0, 0);
}
