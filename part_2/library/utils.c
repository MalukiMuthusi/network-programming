#include "../library/common_headers.h"
#include "function_headers.h"

// print commands to std out for the user
void show_commands()
{
    printf("\nHow can we serve you?\n");
    printf("\t1. Balance.\n");
    printf("\t2. Close Account\n");
    printf("\t3. Withdraw.\n");
    printf("\t4. Statements\n");
    printf("\t5. Deposit\n");
}

// reads the command the user selects
long read_command_input()
{
    char command[8];
    scanf("%s", command);

    // convert string to integer
    errno = 0;
    char *endptr;
    long action = strtol(command, &endptr, 10);
    if (errno != 0)
    {
        perror("Invalid command Entered\n");
        exit(EXIT_FAILURE);
    }
    if (endptr == command)
    {
        fprintf(stderr, "No command was entered\n");
        exit(EXIT_FAILURE);
    }

    return action;
}

// establish a tcp connection
void connect_tcp(const size_t socket_fd, void *server_address)
{
    if ((connect(socket_fd, (struct sockaddr *)server_address, sizeof(*server_address)) < 0))
    {
        throw_error_exit("failed to connect socket");
    }
}