/* =================================================================== 
 *
 *  Trabajo Practico 4 - Ian Finquelstein
 *  
 *  ------------------------------------------------------------------
 *
 *  TOC:
 *  01. Headers & Macros
 *  02. Structures
 *  03. File extension matcher
 *  04. Server
 *
 * =================================================================== */


/* ===================================================================
 *  01. Headers & Macros
 *
 * ------------------------------------------------------------------- */
#include "create_server.h"
#define HTTP_RES "HTTP/1.1 %d %s\r\nContent-Type: %s\r\nContent-Length: %lld\r\n\r\n"

/* ===================================================================
 *  02. Structures
 *
 * ------------------------------------------------------------------- */
struct stat file;//Estructura para fstat().

struct http_field {
    int code;
    char mensaje[32];
};

struct http_field fields[] = {
    {200, "OK"},
    {403, "FORBIDEN"},
    {404, "NOT FOUND"},
    {500, "INTERNAL SERVER ERROR"}
};

struct format_type {
    char type[16];
};

struct format_type mime_types[] = {
    {"image/png"},
    {"image/jpeg"},
    {"image/gif"},
    {"application/pdf"},
    {"text/html"},
    {"text/plain"}
};

struct format_type types[] = {
    {"html"},
    {"jpg"},
    {"png"},
    {"gif"},
    {"pdf"},
    {"jpeg"},
    {"mp4"}
};

//Para atender clientes son cuatro las llamadas al sistema
//requeridas para cumplir casi cualquier tarea. Estas son:
//socket(), bind(), listen(), accept().
//Son n sockets los que se utilizan para manejar peticiones, sin embargo
//el primero sera pasivo para recibir las peticiones y el resto son activos
//o de conexion para ejecutar dichas peticiones

/* ===================================================================
 *  03. File extension matcher
 *
 * ------------------------------------------------------------------- */

int compare_file_ext(char *file_extension)
{
    int type_of_file = 0;
    char html[5];
    strcpy(html, "html");
    char png[4];
    strcpy(png, "png");
    char jpg[4];
    strcpy(jpg, "jpg");
    char pdf[4];
    strcpy(pdf, "pdf");
    char gif[4];
    strcpy(gif, "gif");

    int compare_to_png = strcmp(png, file_extension);
    int compare_to_jpg = strcmp(jpg, file_extension);
    int compare_to_gif = strcmp(gif, file_extension);
    int compare_to_pdf = strcmp(pdf, file_extension);
    int compare_to_html = strcmp(html, file_extension);

    if (compare_to_png == 0)
    {
        type_of_file = 0;//png
    }
    else if (compare_to_jpg == 0)
    {
        type_of_file = 1;//jpg
    }
    else if (compare_to_gif == 0)
    {
        type_of_file = 2;//gif
    }
    else if (compare_to_pdf == 0)
    {
        type_of_file = 3;//pdf
    }
    else if (compare_to_html == 0)
    {
        type_of_file = 4;//html
    }
    else
    {
        printf("El archivo tiene extension desconocida y se mostrará como texto\n");
        type_of_file = 5;//plain text
    }

    return type_of_file;
}

/* ===================================================================
 *  04. Threads
 *
 * ------------------------------------------------------------------- */

//pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *thread_execution(void *s_connect) 
{
    int socket_connect;

    //pthread_mutex_lock(&m1);
    socket_connect = *((int *)s_connect);
    printf("%d\n", socket_connect);
    //pthread_mutex_unlock(&m1);
    if (s_connect != NULL)
        free(s_connect);

    int bytes_read;

    char buffer[1024];//Checkear que los requerimientos entrene en el buffer sino no funciona
    //char *http_method = "GET";

    if((bytes_read = read(socket_connect, buffer, sizeof buffer)) == -1){
        printf("error %s\n", strerror(errno));
    }

    write(socket_connect, "HTTP/1.1 200 OK\r\n", 17);
    if((bytes_read = read(socket_connect, buffer, sizeof buffer)) == -1) {
        printf("error: %s\n", strerror(errno));//Leo del socket hijo para recibir la peticion
        pthread_exit(NULL);
    }

    if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1)
        printf("error: %s\n", strerror(errno));


    //Guardo la primera linea de la cabecera HTTP
    char *token = strtok (buffer, "\r\n");//Parto el mensaje http en su primer linea
    char *http_header_request[1];//*array Creo un puntero a memoria para almacenarla
    char parameters[1024];

    http_header_request[0] = token;//Guardo la cabecera del request en otro lugar para parsearla

    //usar strncpy para copiar un maximo de caracteres
    strcpy(parameters, http_header_request[0]);//Paso la cabecera extraida a un array para parsearlo

    //La parseo en sus 3 parametros
    int j = 0;
    char *token2 = strtok (parameters, " ");//Parseo ahora por espacios
    char *http_header_request_parameters[3];//Array de punteros para guardar los 3 parámetros

    while (token2 != NULL)
    {
        http_header_request_parameters[j++] = token2;//Guardo cada token en el array 
        token2 = strtok (NULL, " ");//Seteo el puntero a NULL y apunto al siguiente salto
    }

    printf("Los parametros son: \n");
    printf("Primero: %s\n", http_header_request_parameters[0]);
    printf("Segundo: %s\n", http_header_request_parameters[1]);
    printf("Tercero: %s\n", http_header_request_parameters[2]);

    //Obtengo la extension del archivo
    char file_extension[16];
    strcpy(file_extension, http_header_request_parameters[1]);

    printf("El archivo pedido es: %s\n", file_extension);

    char *token3 = strtok (file_extension, ".");//Parseo el nombre del archivo pedido para obtener la extension
    char *http_header_request_parameters_extension[1];//Guardo esa extension.

    while (token3 != NULL)
    {
        http_header_request_parameters_extension[0] = token3;
        token3 = strtok (NULL, " ");//Solo me interesa hasta el punto -> lo termino en el espacio
    }

    printf("La extension del archivo es: %s\n", http_header_request_parameters_extension[0]);

    int check_get_method = strcmp(http_header_request_parameters[0], http_method);

    if (check_get_method != 0)//Si metodo != GET -> error sino muestro el recurso pedido
    {
        /* Muestro pagina de error */
        int fd_error;
        fd_error = open("./Error/500.html", O_RDONLY, 0644);

        fstat(fd_error, &file);
        snprintf(buffer, sizeof buffer, HTTP_RES, fields[3].code, fields[3].mensaje, mime_types[4].type, file.st_size);
        if(write(socket_connect, buffer, strlen(buffer)) == -1) //Tener cuidado entre sizeof y strlen cuando escribo al cliente la cabecera http
            printf("error: %s\n", strerror(errno));
        
        while((bytes_read = read(fd_error, buffer, sizeof buffer)) > 0) {//Escribo en el socket el html
            if(write(socket_connect, buffer, bytes_read) == -1)
                printf("error: %s\n", strerror(errno));
        }
        close(fd_error);

        close(socket_connect);

        if (s_connect != NULL)
            free(s_connect);

        pthread_exit(NULL);
        /* Fin pagina de error */
    }
    else 
    {
        char path_to_file[32];//Creo un arreglo para armar la ruta a los archivos
        strcpy(path_to_file, "./Assets");//Le agrego la carpeta
        strcat(path_to_file, http_header_request_parameters[1]);//Le concateno el nombre
        printf("La ruta al archivo es: %s\n", path_to_file);
        int fd;//File descriptor para abrir el archivo solicitado
        if ((fd = open(path_to_file, O_RDONLY, 0644)) > 0)   
        {
            if (fstat(fd, &file) == -1) 
            {//Asocio el fd a un estado para guardar en la estructura ciertos valores como el tamaño
            perror("stat");

            close(socket_connect);

            if (s_connect != NULL)
                free(s_connect);

            pthread_exit(NULL);
            }
            else 
            {
                int type_of_file = compare_file_ext(*http_header_request_parameters_extension);
                snprintf(buffer, sizeof buffer, HTTP_RES, fields[0].code, fields[0].mensaje, mime_types[type_of_file].type, file.st_size);
                if(write(socket_connect, buffer, strlen(buffer)) == -1)//Tener cuidado entre sizeof y strlen cuando escribo al cliente la cabecera http
                    printf("error: %s\n", strerror(errno));
                while((bytes_read = read(fd, buffer, sizeof buffer)) > 0){
                    if(write(socket_connect, buffer, bytes_read) == -1)
                        printf("error: %s\n", strerror(errno));
                }
            }
            close(fd);//Es buena practica cerrar los fd que ya no uso

            close(socket_connect);

            if (s_connect != NULL)
                free(s_connect);

            pthread_exit(NULL);
        }
        else 
        {
            printf("Error: %s\n",strerror(errno));
            printf("%d ", errno);
            switch(errno) 
            {
                case 2:
                    //El archivo no existe
                    printf("El archivo no existe\n");

                    /* Pagina de no encontrado */
                    int fd_not_found;
                    fd_not_found = open("./Error/404.html", O_RDONLY, 0644);

                    fstat(fd_not_found, &file);
                    snprintf(buffer, sizeof buffer, HTTP_RES, fields[2].code, fields[2].mensaje, mime_types[4].type, file.st_size);
                    if(write(socket_connect, buffer, strlen(buffer)) == -1)//Tener cuidado entre sizeof y strlen cuando escribo al cliente la cabecera http
                        printf("error: %s\n", strerror(errno));
                    while((bytes_read = read(fd_not_found, buffer, sizeof buffer)) > 0)
                        if(write(socket_connect, buffer, bytes_read) == -1)
                            printf("error: %s\n", strerror(errno));

                    close(fd_not_found);

                    close(socket_connect);

                    if (s_connect != NULL)
                        free(s_connect);

                    pthread_exit(NULL);
                    /* Fin pagina de no encontrado */
                break;

               case 13:
                    //El archivo no tiene permiso de lectura
                    printf("El archivo no tiene permisos\n");
                    
                    /* Pagina de permiso denegado */
                    int fd_denied;
                    fd_denied = open("./Error/404.html", O_RDONLY, 0644);

                    fstat(fd_denied, &file);
                    snprintf(buffer, sizeof buffer, HTTP_RES, fields[1].code, fields[1].mensaje, mime_types[4].type, file.st_size);
                    if(write(socket_connect, buffer, strlen(buffer)) == -1)//Tener cuidado entre sizeof y strlen cuando escribo al cliente la cabecera http
                        printf("error: %s\n", strerror(errno));
                    while((bytes_read = read(fd_denied, buffer, sizeof buffer)) > 0){
                        if(write(socket_connect, buffer, bytes_read) == -1)
                            printf("error: %s\n", strerror(errno));
                    }

                    close(fd_denied);

                    close(socket_connect);

                    if (s_connect != NULL)
                        free(s_connect);

                    pthread_exit(NULL);          
                    /* Fin pagina permiso denegado */
                break;

                default:
                    strerror(errno);
                    close(socket_connect);
                    if (s_connect != NULL)
                        free(s_connect);
                    pthread_exit(NULL);
               break;
            }
        }
    }
    close(socket_connect);//hijo cierra el socket y termina

    // if (s_connect != NULL)
    //     free(s_connect);

    pthread_exit(NULL);
}

/* ===================================================================
 *  05. Server
 *
 * ------------------------------------------------------------------- */

void create_server(int port_value) 
{
    int socket_listen;
    int socket_connect;
    int val = 1;//Variable necesaria para el seteo de opc. del socket

    socket_listen = socket(AF_INET,SOCK_STREAM,0);//Preparo el socket
    struct sockaddr_in server={};//Estructura de ip puerto local
    server.sin_family = AF_INET;//Familia ip version 4
    server.sin_port = htons(port_value);//Puerto de conexion
    server.sin_addr.s_addr = htonl(INADDR_ANY);//Direccion ip (culaquiera disponible)
    setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val));//Seteo propiedades del socket
    //(un puerto suele mantenerse reservado una vez que se dejo de usar por las dudas un paquete 
    //que llegue tarde pueda ingresar
    if (bind(socket_listen,(struct sockaddr *)&server,sizeof server) != 0)
    {//Bindeo el socket a que escuche en el puerto elegido
        perror("Error en bind");
        exit(EXIT_FAILURE);
    }

    if(listen(socket_listen,10) != 0)
    {//Creo una cola para almacenar peticiones en espera
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    while((socket_connect = accept(socket_listen,NULL,0)) > 0){//Asigno un nuevo socket a cada conexion entrante
        pthread_t thread;
        int *sdc;

        if((sdc = malloc(sizeof (int))) == NULL){
            printf("error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        *sdc = socket_connect;

        printf("%d\n", *sdc);
        if((pthread_create(&thread, NULL, &thread_execution, (void *) sdc)) != 0){
            printf("error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        close(socket_connect);
    }
}
