//QUESTION 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int main()
{

    // definations
    char server_message[256] = "you have reached the server!";
    int server_socket_fd;
    struct sockaddr_in server_address;
    int client_socket_fd;

    // create the socket
    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("socket error: failed to init a socket");
        exit(1);
    }

    //specify an address for the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);              // listening port number
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0

    // TODO(3) use a specic IP address

    //bind the socket to our specified IP and port
    if ((bind(server_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to assign a name to the socket\n");
        printf("error code: %s\n", strerror(errno));
        exit(1);
    }

    // wait for connection
    if ((listen(server_socket_fd, 5)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to mark the fd to be used by the socket");
        exit(1);
    }

    if ((client_socket_fd = accept(server_socket_fd, NULL, NULL)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to accept connection");
        exit(1);
    }

    //send the message
    send(client_socket_fd, server_message, sizeof(server_message), 0);

    //close socket
    if (close(server_socket_fd) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to close client socket");
        exit(1);
    }

    // TODO(1): show message that the server is running and waiting for a client connection
    // TODO(2): fix bug in the client, release all the resources.

    return 0;
}