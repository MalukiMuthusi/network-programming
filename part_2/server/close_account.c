#include "../library/common_headers.h"
#include "../library/function_headers.h"

void close_account(size_t connect_fd)
{
    int n;
    char confirm_buff[8];
    n = recv(connect_fd, confirm_buff, 8, 0);

    if (n == -1)
    {
        printf("error: reading close account confirm message from the socket\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    char *endptr;
    long confirm_number = strtol(confirm_buff, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid confirmation option received from client\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == confirm_buff)
    {
        fprintf(stderr, "no confirmation option was sent by client\n");
        exit(EXIT_FAILURE);
    }

    // send response
    if (send(connect_fd, confirm_buff, 8, 0) < 0)
    {
        printf("failed to write the confirmation message for closing account to the socket\n");
        exit(EXIT_FAILURE);
    }

    printf("server response in close account is: %s\n", confirm_buff);
    exit(EXIT_SUCCESS);
}