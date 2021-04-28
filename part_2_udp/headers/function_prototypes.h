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

#endif