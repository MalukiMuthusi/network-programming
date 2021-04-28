#include "function_prototypes.h"

int main(int argc, char const *argv[])
{
    /* definitions */
    size_t listen_fd;
    struct sockaddr_in server_address, client_address; // IPv4 address structure
    size_t connect_fd;

    /* create the server socket */
    listen_fd = create_udp_socket();

    /* create the server address */
    initialize_address(&server_address, 20000);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    /* assigning a name to the server socket */
    bind_address_to_socket(listen_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    // the server can start accepting messages from client
    for (;;)
    {
        socklen_t len = sizeof(client_address);
        // the PIN
        char pin[96];
        int n = recvfrom(listen_fd, pin, 96, 0, (struct sockaddr *)&client_address, &len);
        if (n == -1)
        {
            // TODO: check errno and return a better error message
            printf("error reading from the socket \n \t error: %s\n", strerror(errno));
            exit(1);
        }

        printf("Your PIN is: %s\n", pin);
    }
    return 0;
}
