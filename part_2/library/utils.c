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
void connect_tcp(size_t *socket_fd, struct sockaddr_in *server_address)
{
    if ((connect(*socket_fd, (struct sockaddr *)server_address, sizeof(*server_address)) < 0))
    {
        throw_error_exit("failed to connect socket");
    }
    printf("Successfuly connected to the server!!");
}

// read pin from std input
char *read_pin()
{
    char *pin;
    scanf("%s", pin);

    errno = 0;
    char *endptr;
    long pin_number = strtol(pin, &endptr, 10);
    // TODO: validate pin
    if (errno != 0)
    {
        throw_error_exit("Invalid Pin Entered");
    }
    if (endptr == pin)
    {
        throw_error_exit("No PIN was entered");
    }

    return pin;
}

// read from a file descriptor to a buffer
ssize_t readn(int fd, void *buffer, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = buffer;

    nleft = n; // initial read = 0 and unread/left = n
    while (nleft > 0)
    {
        if ((nread = read(fd, ptr, nleft)) > 0)
        {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if (nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }

    return (n - nleft);
}

// write to a file descriptor
ssize_t writen(int fd, const void *buffer, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = buffer;
    nleft = n;
    while (nleft > 0)
    {
        if ((nwritten = write(fd, ptr, n)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
            {
                nwritten = 0;
            }
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}