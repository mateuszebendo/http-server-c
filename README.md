# Biblioteca Simples para Servidor TCP em C

## Sobre o Projeto

Este é um módulo em C projetado para simplificar a criação de servidores TCP. Ele encapsula o código repetitivo (boilerplate) necessário para configurar um socket, associá-lo (bind) a uma porta e colocá-lo em modo de escuta (listen).

A ideia é que o desenvolvedor possa focar na lógica de tratamento das conexões, em vez de reescrever o código de inicialização de rede a cada novo projeto.

## Estrutura do Código

O arquivo contém a função `server_constructor`, que age como um "construtor" para uma estrutura `Server`.

- **`server_constructor(...)`**: Esta função recebe os parâmetros de configuração da rede (domínio, porta, etc.) e um ponteiro para uma função `launch`. Ela realiza as chamadas de sistema `socket()`, `bind()` e `listen()`, preparando o servidor para aceitar conexões.

- **Função `launch`**: É a função que contém o loop principal do servidor, onde as conexões são aceitas e tratadas. Ela é passada como argumento para o construtor, tornando o módulo flexível para diferentes aplicações (servidor HTTP, chat, etc.).

## Como Usar

Para usar este módulo, você precisa de três partes:

1. **`server.h`**: Um arquivo de cabeçalho que define a struct `Server`.
2. **`server.c`**: O código que você forneceu.
3. **`main.c`**: O arquivo principal que cria e inicia o servidor.

### Exemplo de server.h

```c
#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

// Estrutura para armazenar as informações do servidor
typedef struct Server {
    int domain;
    int service;
    int protocol;
    unsigned long interface;
    int port;
    int backlog;
    struct sockaddr_in address;
    int socket;
    void (*launch)(struct Server *server);
} Server;

// Protótipo do construtor
Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void(*launch)(Server *));

#endif
```

### Exemplo de main.c

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

#define PORT 8080

// Função que será executada pelo servidor para lidar com conexões
void launch(Server *server)
{
    printf("🚀 Servidor iniciado na porta %d. Aguardando conexões...\n", server->port);
    char buffer[1024];
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nOla, mundo!";

    while (1)
    {
        int client_socket = accept(server->socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Erro ao aceitar conexão");
            continue;
        }

        read(client_socket, buffer, 1024);
        printf("--- Requisição Recebida ---\n%s\n", buffer);
        write(client_socket, response, strlen(response));
        close(client_socket);
    }
}

int main()
{
    // Constrói o servidor usando a função do server.c
    Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, PORT, 10, launch);
    
    // Chama a função de loop principal
    server.launch(&server);

    return 0;
}
```

## Compilação e Execução

1. Salve os três arquivos (`server.h`, `server.c`, `main.c`) no mesmo diretório.

2. Compile o projeto usando um compilador C (como o GCC):

```bash
gcc main.c server.c -o servidor
```

3. Execute o servidor:

```bash
./servidor
```

4. Para testar, abra um navegador e acesse `http://localhost:8080`
