#include "function_prototypes.h"
/* show account balance */
void show_balance(size_t socket_fd)
{
    /* write the show balance command to the server. */

    char buff[8];
    if (snprintf(buff, sizeof(buff), "%d", 1) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write balance command to the buffer.\n");
        exit(1);
    }
    if (send(socket_fd, buff, 8, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write balance to the socket\n");
        exit(1);
    }

    /* read the server's response */
    int n;
    char receiveline[96];
    n = recv(socket_fd, receiveline, 96, 0);

    if (n == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading from the socket\n");
        exit(1);
    }
    /* write the balance amount to user output */
    printf("Your balance is: %s\n", receiveline);
    return;
}
