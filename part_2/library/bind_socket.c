#include "../library/common_headers.h"
#include "../library/function_headers.h"

// bind to socket file descriptor to an address
void bind_socket(size_t *listen_fd, struct sockaddr_in *server_address)
{
    if ((bind(*listen_fd, (struct sockaddr *)server_address, sizeof(*server_address))) < 0)
    {
        throw_error_exit("failed to bind");
    }

    printf("successfuly bind to address\n");
}