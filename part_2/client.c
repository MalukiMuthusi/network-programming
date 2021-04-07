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

// function declarations
void show_balance(size_t socket_fd);
void open_account(size_t socket_fd);
void close_account(size_t socket_fd);

/* Online Banking application client */
int main(int argc, char const *argv[])
{
    size_t socket_fd;
    struct sockaddr_in server_address;

    // Ip address of the server must be provided.
    if (argc != 2)
    {
        printf("Ip address of ther server must be provided\n");
        exit(1);
    }

    // ask for user pin
    printf("Welcome to Digig bank. Enter PIN to proceed.\n");

    // read pin input
    char pin[96];
    scanf("%s", pin);

    // TODO: do validation for the PIN
    errno = 0;
    char *endptr;
    long pin_number = strtol(pin, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid Pin Entered\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == pin)
    {
        fprintf(stderr, "No PIN was entered\n");
        exit(EXIT_FAILURE);
    }

    /* establish a tcp connection with the server */

    //create a socket

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("socket error: failed to init a socket.\n\t error code: %s\n", strerror(errno));
        exit(1);
    }

    //specify an address for the socket
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(20000);

    // convert the IP address from a string(dot notation), to a binary representation
    if (inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0)
    {
        if (errno == EAFNOSUPPORT)
            printf("invalid address provided\n\t error code: %s\n", strerror(errno));
        else
            printf("error occurred converting address\n\t error code: %s\n", strerror(errno));

        exit(1);
    }

    // establish a tcp connection to the server.
    if ((connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0))
    {
        printf("failed to connect socket\n error code: %s\n", strerror(errno));
        // TODO: check the error codes in errno and return meaningful error message
        exit(1);
    }

    // send PIN to the server

    if (send(socket_fd, pin, 96, 0) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write PIN to the socket\n");
        exit(1);
    }

    // show prompt of the next steps user can take
    printf("\nHow can we serve you?\n");
    printf("\t1. Balance.\n");
    printf("\t2. Close Account\n");
    printf("\t3. Withdraw.\n");
    printf("\t4. Open Account\n");
    printf("\t5. Statements\n");

    // read the users service choice
    char command[8];
    scanf("%s", command);

    // convert string to integer
    errno = 0;
    long action = strtol(command, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid command Entered\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == pin)
    {
        fprintf(stderr, "No command was entered\n");
        exit(EXIT_FAILURE);
    }

    switch (action)
    {
    case 1:
        // show balance
        printf("show balance called\n");
        show_balance(socket_fd);
        break;
    case 2:
        // open account
        // open_account(socket_fd);
        close_account(socket_fd);
        break;
    case 3:
        close_account(socket_fd);
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

    printf("Goodbye. See you later. Thank you for banking with us.\n");
    return 0;
}

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

/* open a bank account */
void open_account(size_t socket_fd)
{
    /* write the open account command to the server. */

    char buff[8];
    if (snprintf(buff, sizeof(buff), "%d", 1) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write time to the buffer");
        exit(1);
    }
    if (write(socket_fd, buff, strlen(buff)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write time to the socket");
        exit(1);
    }

    /* server responds with a message that user can continue */

    int n;
    char receiveline[MAXLINE + 1];
    while (((n = read(socket_fd, receiveline, MAXLINE)) > 0))
    {
        receiveline[n] = 0; // null terminate

        /* write the balance amount to user output */
        if (fputs(receiveline, stdout) == EOF)
        {
            // TODO: return a better error message
            printf("error when writing the server's response to the output device\n");
            exit(1);
        }
    }
    if (n == -1)
    {
        // TODO: check errno and return a better error message
        printf("error: reading from the socket\n");
        exit(1);
    }

    /* ask user for their details to open account with */

    /* send user details to the server */

    /* server response with a success or failure in opening account */

    return;
}

/* close online transaction for bank account */
void close_account(size_t socket_fd)
{
    /* write the close account command to the server. */

    char buff[8];
    if (snprintf(buff, sizeof(buff), "%d", 2) < 0)
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

    if (server_confirm_number == 1)
    {
        printf("online banking service closed for this account. please visit our physical office to get service\n");
        return;
    }
    else
        printf("close account aborted!!\n");
}
