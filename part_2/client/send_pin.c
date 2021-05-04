#include "../library/common_headers.h"
#include "../library/function_headers.h"

void send_pin(char *pin, socklen_t socket_fd)
{
    // create a pin message
    char *pin_message;

    int n;
    if ((n = snprintf(pin_message, MAX_BUFF_SIZE, "%s", pin)) < 0)
    {
        throw_error_exit("failed to create a pin message");
    }

    n = writen(socket_fd, pin_message, sizeof(pin_message));

    // if (send(socket_fd, pin_message, sizeof(pin_message), 0) < 0)
    // {
    //     printf("failed to write PIN to the socket\n");
    //     exit(EXIT_FAILURE);
    // }
}