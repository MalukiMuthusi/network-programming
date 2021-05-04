#ifndef FUNCTION_HEADERS
#define FUNCTION_HEADERS

#include "common_headers.h"

void throw_error_exit(char *error_message);
void create_socket(size_t *socket_fd);
void send_pin(char *pin, socklen_t socket_fd);
void show_commands();
long read_command_input();
void connect_tcp(size_t *socket_fd, struct sockaddr_in *server_address);
void provide_service(long action);
char *read_pin();
ssize_t writen(int fd, const void *buffer, size_t n);
ssize_t readn(int fd, void *buffer, size_t n);
#endif