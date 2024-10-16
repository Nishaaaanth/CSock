#include "network.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

struct addrinfo *init_addr(const char *PORT) {
    int status;
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    
    return res;
}

int init_socket(struct addrinfo *res) {
    int sockfd = socket(res->ai_family, res->ai_socktype, 0);
    if(sockfd == 0) {
        std::cout<<"Problem while initializing socket\n";
        exit(EXIT_FAILURE);
    }

    return sockfd;
}


bool bind_socket(int sockfd, struct addrinfo *res) {
    if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        std::cout<<"Error binding socket with IP\n";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int accept_conn(int sockfd) {
    struct sockaddr_storage income_addr;
    socklen_t addr_size = sizeof income_addr;

    int income_sockfd = accept(sockfd, (struct sockaddr *)&income_addr, &addr_size);

    if(income_sockfd == -1) {
        std::cerr<<"Error accepting connection\n";
        exit(EXIT_FAILURE);
    }

    return income_sockfd;
}

bool conn(int sockfd, struct addrinfo *res) {
    if(connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        std::cout<<"Not able to connect\n";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
