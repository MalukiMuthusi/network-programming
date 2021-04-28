#include "function_prototypes.h"
/**
 * @brief check IP address of server is provided
 * 
 * @param argc 
 */
void is_server_address_provided(int argc)
{
    // IP address of the server must be provided.
    if (argc != 2)
    {
        printf("Ip address of ther server must be provided\n");
        exit(1);
    }
}