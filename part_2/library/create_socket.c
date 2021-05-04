#include "../library/common_headers.h"
#include "function_headers.h"
/**
 * create a tcp socket
 *
*/
void create_socket(size_t *socket_fd)
{
    if ((*socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw_error_exit("failed to initialize a socket");
    }
}
