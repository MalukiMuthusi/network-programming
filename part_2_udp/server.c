#include "function_prototypes.h"

int main(int argc, char const *argv[])
{
    /* definitions */
    size_t listen_fd;
    struct sockaddr_in server_address, client_address; // IPv4 address structure
    size_t connect_fd;

    /* create the server socket */
    if ((listen_fd = (socket(AF_INET, SOCK_DGRAM, 0))) < 0)
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

    // the PIN
    char pin[96];

    // the server can start accepting messages from client
    for (;;)
    {
        socklen_t len = sizeof(client_address);
        int n = recvfrom(listen_fd, pin, 96, 0, (struct sockaddr *)&client_address, &len);
        if (n == -1)
        {
            // TODO: check errno and return a better error message
            printf("error: reading from the socket\n");
            exit(1);
        }

        printf("Your PIN is: %s\n", pin);
    }
    return 0;
}
