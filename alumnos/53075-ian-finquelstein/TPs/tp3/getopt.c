#include "getopt.h"

// Imprime por pantalla informacion para el programa
void print_usage (FILE* stream, int exit_code)
{
  fprintf(stream, "Usage: options [ inputfile ...]\n");
  fprintf(stream,
    " -h  --help                Muestra este mensaje de info.\n"
    " -i  --input filename      Nombre de archivo de entrada.\n"
    " -n  --number amount       Cantidad de hijos a crear.\n");

  exit(exit_code);
}

void get_opt(int argc, char* argv[], char* input_filename, char* number_of_children)
{
  int next_option;
  //Una cadena que lista las opciones abreviadas
  const char* const short_options = "hi:n:";
  //Un array que describe un array de opciones no abreviadas
  //Lo primero describe el nombre de la opciones
  //Lo segundo es 1 si toma argumentos y 0 sino
  //El tercero es NULL y el cuarto la opc. abreviada
  const struct option long_options[] = {
    { "help",       0, NULL, 'h'},
    { "input",      1, NULL, 'i'},
    { "numchilds",  1, NULL, 'n'},
    { NULL,         0, NULL, 0  }
  };


  do {
    //Para usar getopt_long debo especificar dos tipos de datos
    //El primero es un string con las opciones abreviadas
    //El segundo un array de struct con las opciones no abreviadas
    next_option = getopt_long(argc, argv, short_options,
                                          long_options, NULL);
    switch (next_option) {
      case 'h':
        //Imprimir por salida estandar el mensajes
        //y terminar con exit code 0 (terminacion normal)
        print_usage(stdout, 0);
        break;

      case 'i':
        //La variable global optarg apunta al texto del argumento
        for(int i = 0; i < strlen(optarg); i++)
        {
          *(input_filename+i) = *(optarg+i);
        }
        break;

      case 'n':
        for(int i = 0; i < strlen(optarg); i++)
        {
          *(number_of_children+i) = *(optarg+i);
        }
        break;

      case '?':
        //Imprimir por salida de error estandar
        //terminar con codigo 1 (terminacion abnormal)
        print_usage(stderr, 1);
        break;

      case -1:
        //Cuando getopt_long termina de leer las opciones
        break;

      default:
        //algun imprevisto
        abort();
    }
  } while(next_option != -1); //devuelve -1 si no encuentra mas opciones
}
