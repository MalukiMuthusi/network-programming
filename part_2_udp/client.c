/* custom functions */
#include "function_prototypes.h"

int main(int argc, char const *argv[])
{
    size_t socket_fd;
    struct sockaddr_in server_address;

    // IP address of the server must be provided.
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

    //create a socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
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

    // send PIN to the server
    if ((sendto(socket_fd, pin, sizeof(pin), 0, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to write PIN to the socket\n");
        exit(1);
    }

    // show the services offered
    services_offered();

    // read the user's service choice
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
        // show_balance(socket_fd);
        break;
    case 2:
        printf("close account\n");
        // close_account(socket_fd);
        break;
    case 3:
        printf("withdraw amount\n");
        // withdraw(socket_fd);
        break;
    case 4:
        printf("open account\n");
        // open_account(socket_fd);
        break;
    default:
        break;
    }

    printf("Goodbye. Thank you for banking with us.\n");
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
