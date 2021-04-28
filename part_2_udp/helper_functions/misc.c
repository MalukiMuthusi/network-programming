#include "function_prototypes.h"

/**
 * @brief Convert a string to number
 * 
 * @param buffer 
 * @param name 
 */
long read_number_input(char *buffer, const char *name)
{
    errno = 0;
    char *endptr;
    long pin_number = strtol(buffer, &endptr, 10);
    if (errno != 0)
    {
        fprintf(stderr, "Invalid %s Entered\n", name);
        exit(EXIT_FAILURE);
    }
    if (endptr == buffer)
    {
        fprintf(stderr, "No %s was entered\n", name);
        exit(EXIT_FAILURE);
    }

    return pin_number;
}

/**
 * @brief Create a tcp socket object
 * 
 * @param socket_fd 
 */
size_t create_udp_socket()
{
    size_t socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket error: failed to init a socket.\n\t error code: %s\n", strerror(errno));
        exit(1);
    }

    return socket_fd;
}

/**
 * @brief Initialize a server address
 * 
 * @param server_address 
 * @param port_number 
 */
void initialize_address(struct sockaddr_in *server_address, size_t port_number)
{
    memset(server_address, 0, sizeof(*server_address));
    (*server_address).sin_family = AF_INET;
    (*server_address).sin_port = htons(port_number);
}

/**
 * @brief assign an ip address from a string to the server address
 * 
 * @param address 
 * @param buff 
 */
void assign_address_from_string(void *address, const char *buff)
{
    if (inet_pton(AF_INET, buff, address) <= 0)
    {
        if (errno == EAFNOSUPPORT)
            printf("invalid address provided\n\t error code: %s\n", strerror(errno));
        else
            printf("error occurred converting address\n\t error code: %s\n", strerror(errno));

        exit(EXIT_FAILURE);
    }
}

/**
 * @brief send a message to a server
 * 
 * @param error_message 
 * @param socket_fd 
 * @param buf 
 * @param server_address 
 */
void send_message(const char *error_message, const size_t socket_fd, const char *buf, const struct sockaddr_in *server_address)
{
    if ((sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)server_address, sizeof(*server_address))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("%s\n\t error: %s\n", error_message, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void bind_address_to_socket(const size_t fd, const struct sockaddr *addr, socklen_t len)
{
    /* assigning a name to the server socket */
    if ((bind(fd, addr, len)) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to assign a name to the socket.\n\t error code: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}