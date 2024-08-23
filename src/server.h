// server.h

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

typedef struct {
    int domain;
    int service;
    int protocol;
    unsigned long interface;
    int port;
    int backlog;
    void (*launch)(struct Server *);
    int socket;
    struct sockaddr_in address;
} Server;

Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void (*launch)(Server *));

#endif // SERVER_H
