#include "../library/common_headers.h"
#include "../library/function_headers.h"
/* close online transaction for bank account */
void close_account(size_t socket_fd)
{
    /* write the close account command to the server. */

    char buff[8];
    if (snprintf(buff, sizeof(buff), "%d", 2) < 0)
    {
        printf("failed to write close account command the buffer\n");
        exit(1);
    }
    if (send(socket_fd, buff, 8, 0) < 0)
    {
        printf("failed to write close account command to the socket\n");
        exit(1);
    }
    printf("confirm you want close account.\n\t 1. Yes\n\t 2. No\n");
    char confirm[8];
    scanf("%s", confirm);

    errno = 0;
    char *endptr;
    long confirm_number = strtol(confirm, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid confirmation number Entered\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == confirm)
    {
        fprintf(stderr, "No confirmation number was entered\n");
        exit(EXIT_FAILURE);
    }

    if (send(socket_fd, confirm, 8, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write confirm number to the socket\n");
        exit(1);
    }

    /* server responds with a message that user can continue */

    char serv_response[8];
    if ((recv(socket_fd, serv_response, 8, 0)) == -1)
    {
        printf("error: reading from the socket\n");
        exit(1);
    }

    //proccess server's response
    errno = 0;
    char *endptr2;
    long server_confirm_number = strtol(serv_response, &endptr2, 10);
    if (errno != 0)
    {
        perror("Invalid response from server\n");
        exit(EXIT_FAILURE);
    }
    if (endptr2 == serv_response)
    {
        fprintf(stderr, "server returned wrong response\n");
        exit(EXIT_FAILURE);
    }

    if (server_confirm_number == 1)
    {
        printf("online banking service closed for this account. please visit our physical office to get service\n");
        return;
    }
    else
        printf("close account aborted!!\n");
}
