/* common includes */

#ifndef FUNCTION_HEADERS
#define FUNCTION_HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
void services_offered();
void show_balance(size_t socket_fd);
void open_account(size_t socket_fd);
void close_account(size_t socket_fd);
void withdraw(size_t socket_fd);
void open_account(const size_t socket_fd);

void is_server_address_provided(int argc);
long read_number_input(char *buffer, const char *name);
size_t create_udp_socket();
void initialize_address(struct sockaddr_in *server_address, size_t port_number);
void assign_address_from_string(void *address, const char *buff);
void send_message(const char *error_message,const size_t socket_fd,const char *buf,const struct sockaddr_in *server_address);
void bind_address_to_socket(const size_t fd, const struct sockaddr *addr, socklen_t len);

#endif