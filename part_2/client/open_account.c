#include "../library/common_headers.h"
#include "../library/function_headers.h"

/* open a bank account */
void open_account(const size_t socket_fd)
{
    /* write the open account command to the server. */
    char buff[8];
    if (snprintf(buff, sizeof(buff), "%d", 4) < 0)
    {
        printf("failed to write open account command to the buffer\n");
        exit(1);
    }
    if (send(socket_fd, buff, 8, 0) < 0)
    {
        printf("failed to write open account command to the socket\n");
        exit(1);
    }

    /* server responds with a message that user can continue */

    /* ask user for their details to open account with */
    printf("Enter details to create account. \n");

    char full_name[64];
    printf("\t Enter first name: ");
    scanf("%s", full_name);

    char date_birth[64];
    printf("\tDate of birth:  ");
    scanf("%s", date_birth);

    printf("Select account type: \n\t 1. Basic Account. \n\t 2. Savings Account.\n");
    char account_type[8];
    scanf("%s", account_type);

    /* send user details to the server */

    // send full names
    if (send(socket_fd, full_name, 64, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write full names to the socket\n");
        exit(1);
    }

    // send date of birth
    if (send(socket_fd, date_birth, 64, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write date of birth to the socket\n");
        exit(1);
    }

    // send account type
    if (send(socket_fd, account_type, 8, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write account type to the socket\n");
        exit(1);
    }

    /* server response with a success or failure in opening account */
    char serv_response_buff[8];
    if ((recv(socket_fd, serv_response_buff, 8, 0)) == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading from the socket\n");
        exit(1);
    }

    errno = 0;
    char *endptr;
    long serv_response = strtol(serv_response_buff, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid confirmation number Entered\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == serv_response_buff)
    {
        fprintf(stderr, "No confirmation number was entered\n");
        exit(EXIT_FAILURE);
    }

    if (serv_response != 1)
    {
        printf("failed to create account.\n");
        return;
    }

    printf("account created\n");

    return;
}
