#include "getopt.h"

// Imprime por pantalla informacion para el programa
void print_usage (FILE* stream, int exit_code)
{
  fprintf(stream, "Usage: options [ inputfile ...]\n");
  fprintf(stream,
    " -h  --help                Muestra este mensaje de info.\n"
    " -p  --port                Numero de puerto.\n");

  exit(exit_code);
}

int get_opt(int argc, char* argv[]){
    int port_value = 0;

    int getopt_opt;
    opterr = 0;
 
    while ((getopt_opt = getopt (argc, argv, "hp:")) != -1) {
         switch(getopt_opt)
         {
         	case 'h':
         		print_usage(stdout, 0);
         		break;

            case 'p':
                port_value = atoi(optarg);
                break;
 
            case '?':
                if (optopt == 'p')
                    fprintf (stderr, "La opcion -p requiere un argumento\n");
                else if (isprint (optopt))//checkea que un caracter pueda ser impreso
                    fprintf (stderr, "Opcion desconocida -%c.\n", optopt);
                	print_usage(stdout, -1);
                break;
 
            default:
                abort ();
        }
    }

    if (port_value == 0)
    {		
    	port_value = 5000;
    	return port_value;
    }
    else
    {
    	return port_value;
    }
}

