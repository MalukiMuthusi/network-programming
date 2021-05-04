#include "../library/common_headers.h"
#include "../library/function_headers.h"

/* return an accounts balance amount */
void show_balance(size_t connect_fd)
{
    // write balance amount to the client
    char buff[96];
    if (snprintf(buff, 96, "%s", "1000") < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write time to the buffer\n");
        exit(1);
    }
    if (send(connect_fd, buff, 96, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write time to the socket\n");
        exit(1);
    }
    printf("\nresponded balance amount of: 1000 to the client\n");
    exit(EXIT_SUCCESS);
}