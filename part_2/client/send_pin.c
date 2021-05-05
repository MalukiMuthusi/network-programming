#include "../library/common_headers.h"
#include "../library/function_headers.h"

void send_pin(char *pin, socklen_t socket_fd)
{
    // create a pin message
    char pin_message[MAX_BUFF_SIZE];

    int n;
    if ((n = snprintf(pin_message, MAX_BUFF_SIZE, "%s", pin)) < 0)
    {
        throw_error_exit("failed to create a pin message");
    }

    printf("sending to server PIN: %s\n", pin_message);
    n = writen(socket_fd, pin_message, sizeof(pin_message));
}