//QUESTION 4a
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//network header files
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(int argc, char **argv){                    // Enable us to put the port number or file name as a CMD argument
  if(argc != 2){                                    //Arguments are 2, port number or file name
    printf("Usage: %s <port number>\n", argv[0]);  //Error if argument is not declared
    exit(0);
  }

  int port = atoi(argv[1]);
  int socket_fd;
  struct sockaddr_in server_address, client_address;
  char buffer[1024];
  socklen_t addr_size;

  //Creating the UDP server socket

  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&server_address, '\0', sizeof(server_address));

  // Specifying an address and port number for the socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);                           // Port number specification
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");        // IP address specification


  //binding IP address and the port number
  bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address));
  addr_size = sizeof(client_address);

  //Receiving data
  recvfrom(socket_fd, buffer, 1024, 0, (struct sockaddr*)& client_address, &addr_size);
  printf("[+]Data Received: %s", buffer);   //Server responding

}
