#include "../library/common_headers.h"
#include "../library/function_headers.h"

int main(int argc, char const *argv[])
{
    /* definitions */
    size_t listen_fd;
    struct sockaddr_in server_address; // IPv4 address structure
    size_t connect_fd;

    /* create the server socket */
    create_socket(&listen_fd);

    /* create the server address */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(20000);

    // bind to an address
    bind_socket(&listen_fd, &server_address);

    // start listening for client requests
    listen_socket(&listen_fd, 10);

    for (;;)
    {
        // accept a tcp connection request. get the clients details, ip address, port number
        accept_socket(&connect_fd, &listen_fd);

        // message from client
        read_message(connect_fd);
        continue;

        // check service to offer from the message
        void *m;
        int service = check_service(m);

        switch (service)
        {
        case 0:
            printf("invalid service\n");
        case 1:
            // show balance

            printf("show_balance(connect_fd);");

            break;
        case 2:
            // open account

            printf("close_account(connect_fd)");

            break;
        case 3:

            printf("withdraw(connect_fd)");

            // close account
            break;
        case 4:
            printf("open_account(socket_fd);");
            // withdraw amount
            break;
        case 5:
            // account statements
            printf("deposit_money");
            break;

        default:
            printf("invalid service\n");
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
