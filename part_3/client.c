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

int main(int argc, char const *argv[])
{

    // definitions
    size_t socket_fd;
    struct sockaddr_in server_address;

    //create a socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("socket error: failed to init a socket");
        exit(1);
    }

    //specify an address for the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);

    // Ip address of the server must be provided.
    if (argc != 2)
    {
        printf("Ip address of ther server must be provided\n");
        exit(1);
    }

    // convert the IP address from a string(dot notation), to a binary representation
    if (inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0)
    {
        if (errno == EAFNOSUPPORT)
            printf("invalid address provided\n");
        else
            printf("error occurred converting address\n");

        exit(1);
    }

    // establish a tcp connection to the server.
    if ((connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0))
    {
        printf("failed to connect socket\n error code: %s\n", strerror(errno));
        // TODO: check the error codes in errno and return meaningful error message
        exit(1);
    }

    //receive data from the server
    char server_response[256];
    recv(socket_fd, &server_response, sizeof(server_response), 0);

    //print out the server's response
    printf("The server sent the data %s\n", server_response);

    //close the socket
    close(socket_fd);

    return 0;
}