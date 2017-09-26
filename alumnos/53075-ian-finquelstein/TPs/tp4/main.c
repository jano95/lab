#include "create_server.h"
#include "getopt.h"

int 
main(int argc, char* argv[])
{
	int port_value;
	port_value = get_opt(argc, argv);

    create_server(port_value);
    return 0;
}
