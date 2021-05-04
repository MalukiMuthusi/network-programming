#include "../library/common_headers.h"
#include "../library/function_headers.h"

void listen_socket(size_t *listen_fd, int queue_n)
{
    if ((listen(*listen_fd, queue_n) < 0))
    {
        throw_error_exit("failed to start listening for connection");
    }

    printf("started listening for client requests\n");
}