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

int main(int argc, char const *argv[])
{
    /* definitions */
    size_t listen_fd;
    struct sockaddr_in server_address;
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
            // TODO: check the errno and return more meaningful error codes
            printf("failed to accept connection.\n\t error code: %s\n", strerror(errno));
            exit(1);
        }
        else
            printf("successfully connected to client!!\n");

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
            show_balance(connect_fd);
            break;
        case 2:
            // open account
            break;
        case 3:
            // close account
            break;
        case 4:
            // withdraw amount
            break;
        case 5:
            // account statements
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
}
