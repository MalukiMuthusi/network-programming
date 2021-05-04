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

        pid_t child;

        /* start: offer service to the client */

        // read message from client, user's PIN
        long pin = read_pin_from_client(&connect_fd);

        /* write the PIN to user output */
        printf("User's pin is: \n\t%ld\n", pin);

        // read the command user selects to get service.
        long action_command = select_service(&connect_fd);

        /* write the command to user output */
        printf("Received command: \n\t%ld\n", action_command);

        switch (action_command)
        {
        case 1:
            // show balance
            if ((child = fork()) == 0)
            {
                close(listen_fd);
                printf("show_balance(connect_fd);");
                exit(EXIT_SUCCESS);
            }
            break;
        case 2:
            // open account
            if ((child = fork()) == 0)
            {
                close(listen_fd);
                printf("close_account(connect_fd)");
                exit(EXIT_SUCCESS);
            }
            break;
        case 3:
            if ((child = fork()) == 0)
            {
                close(listen_fd);
                printf("withdraw(connect_fd)");
                exit(EXIT_SUCCESS);
            }
            // close account
            break;
        case 4:
            // withdraw amount
            break;
        case 5:
            // account statements
            printf("open_account(connect_fd)");
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
