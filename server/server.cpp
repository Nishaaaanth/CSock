#include "../include/network.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr const char PORT[] = "3000";
constexpr const char msg[BUFF] = "Hi Client!";
char server_addr_presentation[INET_ADDRSTRLEN];

int main() {
  struct addrinfo *server_addr = init_addr(PORT);
  int server_sockfd = init_socket(server_addr);
  bind_socket(server_sockfd, server_addr);

  if (listen(server_sockfd, QUEUE) == -1) {
    std::cerr << "Error while listening to the port: " << PORT << '\n';
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening to port: " << PORT << '\n';
  int client_sockfd = accept_conn(server_sockfd);

  inet_ntop(server_addr->ai_family, (struct sockaddr_in *)server_addr->ai_addr,
            server_addr_presentation, server_addr->ai_addrlen);

  int len = strlen(msg);
  if (send(client_sockfd, msg, len, 0) == -1) {
    std::cerr << "Error sending the message\n";
    exit(EXIT_FAILURE);
  }

  std::cout << "Connected with: " << server_addr_presentation << '\n';
  close(client_sockfd);
  std::cout << "Connection closed with: " << server_addr_presentation << '\n';

  close(server_sockfd);
  freeaddrinfo(server_addr);

  return 0;
}
