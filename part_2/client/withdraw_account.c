#include "../library/common_headers.h"
#include "../library/function_headers.h"

void withdraw(size_t socket_fd)
{
    /* write the withdraw command to the server. */
    char buff[8];
    if (snprintf(buff, sizeof(buff), "%d", 3) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write close account command the buffer\n");
        exit(1);
    }
    if (send(socket_fd, buff, 8, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write close account command to the socket\n");
        exit(1);
    }

    // ask user how much they want to withdraw
    printf("Enter the amount to withdraw.\n");
    char withdraw_amount_buff[64];
    scanf("%s", withdraw_amount_buff);

    errno = 0;
    char *endptr;
    long withdraw_amount = strtol(withdraw_amount_buff, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid withdraw amount Entered\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == withdraw_amount_buff)
    {
        fprintf(stderr, "No amount was entered\n");
        exit(EXIT_FAILURE);
    }

    if (send(socket_fd, withdraw_amount_buff, 64, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write withdraw amount to the socket\n");
        exit(1);
    }

    // read the server's response

    int n;
    char serv_response[8];
    n = recv(socket_fd, serv_response, 8, 0);
    if (n == -1)
    {
        // TODO: check errno and return a better error message
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

    if (server_confirm_number == withdraw_amount)
    {
        printf("Withdraw amount success!!\n");
        return;
    }
    else
        printf("failed to withdraw amount!!\n");
}