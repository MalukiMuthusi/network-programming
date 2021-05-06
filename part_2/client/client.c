#include "../library/common_headers.h"
#include "../library/function_headers.h"

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

    /* establish a tcp connection with the server */

    //create a socket
    create_socket(&socket_fd);

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
    connect_tcp(&socket_fd, &server_address);

    printf("Welcome to Digig bank.\n");

    int ask_commands = 1;
    while (ask_commands)
    {
        // show prompt of the next steps user can take
        show_commands();

        // read the user's service choice
        long action = read_command_input();

        // provide the service chosen
        ask_commands = provide_service(action, socket_fd);
    }

    printf("Goodbye. Thank you for banking with us.\n");
    return 0;
}