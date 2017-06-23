#include "fileSize.h"

int file_size(char *input_filename)
{
    FILE *input;
    int position;

    input=fopen(input_filename,"r");

    fseek(input, 0, SEEK_END);
    position = ftell(input);
    fclose(input);

    return position;
}
