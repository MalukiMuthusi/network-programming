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
void bind_socket(size_t *listen_fd, struct sockaddr_in *server_address);
void listen_socket(size_t *listen_fd, int queue_n);
void accept_socket(size_t *connect_fd, size_t *listen_fd);
long read_pin_from_client(size_t *connect_fd);
long string_to_number(char *string, char *error_1, char *error_2);
long select_service(size_t *connect_fd);
#endif