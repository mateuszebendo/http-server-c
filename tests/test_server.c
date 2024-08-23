/*
*  -> Considerações sobre o código:
*
*    0. Esse código foi feito com intuito meramente recreativo, então sinta-se
*    convidado a aprimora-lo e fazer com que ele fique algo mais profissional.
*
*    1. Vi essa ideia de comentar o código dessa forma no github enquanto procurava
*    material de referência e achei genial. Dito isso, esse código deve ficar
*    semelhante a uma bíblia de tanto comentário.
*
*    2. O que são File Descriptors (fd):
*    File descriptors (FD) são números inteiros que o sistema operacional utiliza
*    para representar e gerenciar recursos de entrada/saída, como arquivos, sockets,
*    pipes e dispositivos. Eles atuam como ponteiros abstratos que permitem que
*    programas acessem e manipulem esses recursos de forma unificada.
*/

#include <stdio.h>
#include "../src/server.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void launch(Server server)
{
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";

    printf("Servidor rodando na porta %d\n", PORT);

    while(1)
    {
        printf("\tEsperando clientes se conectarem...\n");

        struct sockaddr_in client_addr;
        int client_addr_len = sizeof(client_addr);

        int client_fd = accept(server.socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_fd == -1)
        {
        perror("Falha na conexão com o cliente\n");
        exit(-1);
        }

        read(client_fd, buffer, BUFFER_SIZE);
        printf("\tRequisição recebida com sucesso!\n");

        write(client_fd, response, strlen(response));
        close(client_fd);
    }
}

int main()
{
    Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, PORT, 10, launch);
    server.launch(&server);
}