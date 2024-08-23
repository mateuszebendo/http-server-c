#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"

#define PORT 8080
#define BUFFER_SIZE 1024

Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void(*launch)(Server *))
{
    Server server;

    server.domain = domain; 
    server.service = service; 
    server.protocol = protocol; 
    server.interface = interface;
    server.port = port; 
    server.backlog = backlog;
    server.launch = launch;

    server.address.sin_family = domain; 
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain, service, protocol);
    if(server.socket == 0)
    {
      perror("Erro ao se conectar com o soquete\n");
      exit(EXIT_FAILURE);
    }

    if(bind(server.socket, (struct serveraddr*)&server.address, sizeof(server.address)) < 0)
    {
      perror("Erro ao bindar\n");
      exit(EXIT_FAILURE);
    }

    if(listen(server.socket, server.backlog) < 0)
    {
      perror("Erro ao escutar\n");
      exit(EXIT_FAILURE);
    }

    return server;
}