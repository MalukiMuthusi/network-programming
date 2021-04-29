/* common includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

/* macros */
#define MAXLINE 4096

/* function declarations */
void show_balance(size_t connect_fd);
void close_account(size_t connect_fd);
void withdraw(size_t connect_fd);
void open_account(const size_t connect_fd);

int main(int argc, char const *argv[])
{
    /* definitions */
    size_t listen_fd;
    struct sockaddr_in server_address; // IPv4 address structure
    size_t connect_fd;

    /* create the server socket */

    if ((listen_fd = (socket(AF_INET, SOCK_STREAM, 0))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("socket error: failed to init a socket.\n\t error code: %s\n", strerror(errno));
        exit(1);
    }

    /* create the server address */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(20000);

    /* assigning a name to the server socket */
    if ((bind(listen_fd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to assign a name to the socket.\n\t error code: %s\n", strerror(errno));
        exit(1);
    }

    /* mark the passive socket that will be used to accept incoming connection requests */
    if ((listen(listen_fd, 10) < 0))
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to mark the fd to be used by the socket.\n\t error code: %s\n", strerror(errno));
        exit(1);
    }

    for (;;)
    {
        // accept a tcp connection request. get the clients details, ip address, port number
        if ((connect_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL)) < 0)
        {
            printf("failed to accept connection.\n\t error code: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
            printf("successfully connected to client!!\n");

        pid_t child;

        /* start: offer service to the client */

        // read message from client, user's PIN
        int n;
        char pin[96];
        n = recv(connect_fd, pin, 96, 0);

        if (n == -1)
        {
            // TODO: check errno and return a better error message
            printf("error: reading PIN from the socket\n");
            exit(1);
        }

        /* write the PIN to user output */
        printf("User's pin is: \n\t%s\n", pin);

        // read the command user selects to get service.
        n = 0;
        char action_command[8];
        n = recv(connect_fd, action_command, 8, 0);
        if (n == -1)
        {
            // TODO: check errno and return a better error message
            printf("error: reading action command from the socket\n");
            exit(1);
        }

        action_command[n] = 0; // null terminate

        /* write the command to user output */
        printf("Received command: \n\t%s\n", action_command);

        errno = 0;
        char *endptr;
        long command = strtol(action_command, &endptr, 10);
        if (errno != 0)
        {
            perror("failed to convert command to int.\n");
            exit(EXIT_FAILURE);
        }
        if (endptr == action_command)
        {
            fprintf(stderr, "No command was found.\n");
            exit(EXIT_FAILURE);
        }
        switch (command)
        {
        case 1:
            // show balance
            if ((child = fork()) == 0)
            {
                close(listen_fd);
                show_balance(connect_fd);
                exit(EXIT_SUCCESS);
            }
            break;
        case 2:
            // open account
            if ((child = fork()) == 0)
            {
                close(listen_fd);
                close_account(connect_fd);
                exit(EXIT_SUCCESS);
            }
            break;
        case 3:
            if ((child = fork()) == 0)
            {
                close(listen_fd);
                withdraw(connect_fd);
                exit(EXIT_SUCCESS);
            }
            // close account
            break;
        case 4:
            // withdraw amount
            break;
        case 5:
            // account statements
            open_account(connect_fd);
            break;

        default:
            break;
        }

        /* end: offer service to the client */

        // close connection with the client
        if (close(connect_fd) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write time to the socket.\n");
            exit(1);
        }
    }
    return 0;
}

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
