#include "getopt.h"
#include "process.h"
#include "createSharedMemory.h"
#include "writeSharedMemory.h"
#include "fileSize.h"

int
main(int argc, char* argv[])
{
  //Creo las variables para poder guardar
  //y luego manipular los parametros que recibe el programa
  char* input_filename = (char*)malloc(sizeof(char));
  char* number_of_children = (char*)malloc(sizeof(char));
  //Manejo las opciones
  get_opt(argc, argv, input_filename, number_of_children);
  //Averiguo cuanto pesa el archivo para dinamicamente crear el espacio de m. compartida
  int amount = file_size(input_filename);
  //Creo el espacio de memoria compartida
  char *shm = create_shared_memory(amount);
  //Escribo en memoria compartida
  write_shared_memory(input_filename, shm);
  //Lanzo los procesos
  launch_Process(atoi(number_of_children), shm);

  return 0;
}
