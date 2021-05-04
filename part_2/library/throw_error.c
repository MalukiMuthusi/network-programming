#include "common_headers.h"

/*
* throw an error message and exit
*/
void throw_error_exit(char *error_message)
{
    printf("%s\nerror code: %s", error_message,strerror(errno));
    exit(EXIT_FAILURE);
}