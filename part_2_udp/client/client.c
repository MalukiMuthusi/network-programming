/* custom functions */
#include "../headers/function_prototypes.h"

int main(int argc, char const *argv[])
{
    size_t socket_fd;
    struct sockaddr_in server_address;

    // IP address of the server must be provided.
    is_server_address_provided(argc);

    // ask for user pin
    printf("Welcome to Digig bank. Enter PIN to proceed.\n");

    // read pin input
    char pin[96];
    scanf("%s", pin);

    // TODO: do validation for the PIN
    long pin_number = read_number_input(pin, "PIN");

    //create a socket
    socket_fd = create_udp_socket(socket_fd);

    //specify an address for the socket
    initialize_address(&server_address, 20000);

    // convert the IP address from a string(dot notation), to a binary representation
    assign_address_from_string(&server_address.sin_addr, argv[1]);

    // send PIN to the server
    send_message("failed to write PIN to the socket", socket_fd, pin, &server_address);

    // show the services offered
    services_offered();

    // read the user's service choice
    char command[8];
    scanf("%s", command);

    // convert string to integer
    long action = read_number_input(command, "command");
    
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