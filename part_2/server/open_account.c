#include "../library/common_headers.h"
#include "../library/function_headers.h"

void open_account(const size_t connect_fd)
{
    // receive the full names
    char full_name[64];
    if ((recv(connect_fd, full_name, 64, 0)) == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading full name  from the socket\n");
        exit(1);
    }

    // receive the date of birth

    char date_birth[64];
    if ((recv(connect_fd, date_birth, 64, 0)) == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading date of birth from the socket\n");
        exit(1);
    }

    // receive the account type
    char account_type[64];
    if ((recv(connect_fd, account_type, 8, 0)) == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading account type from the socket\n");
        exit(1);
    }

    // send response
    char response_buff[8];
    if ((strcmp(full_name, "") > 0) && (strcmp(date_birth, "") > 0) && (strcmp(account_type, "") > 0))
    {
        if (snprintf(response_buff, 8, "%d", 1) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write close account command the buffer\n");
            exit(1);
        }
        if (send(connect_fd, response_buff, 8, 0) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write withdraw amount to the socket\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (snprintf(response_buff, 8, "%d", 2) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write server response to the buffer\n");
            exit(1);
        }
        if (send(connect_fd, response_buff, 8, 0) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write server response to the socket\n");
            exit(EXIT_FAILURE);
        }
    }
}
