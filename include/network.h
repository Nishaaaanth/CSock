#ifndef NETWORK_H
#define NETWORK_H
#define BUFF 100
#define QUEUE 10

struct addrinfo *init_addr(const char *);
int init_socket(struct addrinfo *);
bool bind_socket(int, struct addrinfo *);
int accept_conn(int);
bool conn(int, struct addrinfo *);

#endif
