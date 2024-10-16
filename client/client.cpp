#include "../include/network.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr char const PORT[] = "3000";
size_t buff_bytes;
char msg[BUFF];
char server_addr_presentation[INET_ADDRSTRLEN];

int main() {
  struct addrinfo *server_addr = init_addr(PORT);
  int server_sockfd = init_socket(server_addr);

  inet_ntop(server_addr->ai_family, (struct sockaddr_in *)server_addr->ai_addr,
            server_addr_presentation, server_addr->ai_addrlen);
  std::cout << "connecting to: " << server_addr_presentation << '\n';

  conn(server_sockfd, server_addr);

  if ((buff_bytes = recv(server_sockfd, msg, BUFF - 1, 0)) == -1) {
    std::cerr << server_sockfd << ": Error while receiving data\n";
    exit(EXIT_FAILURE);
  }

  msg[buff_bytes] = '\0';
  std::cout << "Message is: " << msg << '\n';

  close(server_sockfd);
  freeaddrinfo(server_addr);

  return 0;
}
