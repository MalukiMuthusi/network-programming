#include "../library/common_headers.h"
#include "../library/function_headers.h"

void accept_socket(size_t *connect_fd, size_t *listen_fd)
{
    if ((*connect_fd = accept(*listen_fd, (struct sockaddr *)NULL, NULL)) < 0)
    {
        throw_error_exit("failed to accept client request!!!\n");
    }
    else
        printf("successfully connected to client!!\n");
}