#ifndef _create_server_h_
#define _create_server_h_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void *thread_execution(void* socket_connect);
void create_server(int port_value);
int compare_file_ext(char *file_extension);

#endif