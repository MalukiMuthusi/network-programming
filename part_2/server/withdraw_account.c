#include "../library/common_headers.h"
#include "../library/function_headers.h"

void withdraw(size_t connect_fd)
{
    // read the withdraw amount from the socket
    int n;
    char withdraw_amount_buff[64];
    n = recv(connect_fd, withdraw_amount_buff, 64, 0);

    if (n == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading withdraw amount  message from the socket\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    char *endptr;
    long withdraw_amount = strtol(withdraw_amount_buff, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid withdraw amount received from client\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == withdraw_amount_buff)
    {
        fprintf(stderr, "no withdraw amount was sent by client\n");
        exit(EXIT_FAILURE);
    }

    if (send(connect_fd, withdraw_amount_buff, 64, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write withdraw amount to the socket\n");
        exit(EXIT_FAILURE);
    }
    printf("client wishes to withdraw: %ld\n", withdraw_amount);

    // response with withdraw success or failure

    exit(EXIT_SUCCESS);
}