#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

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

int main(){
  int server_fd; //<- Variavel usada para genereciar a entrada e saida de dados pelo soquete.

  /* Cria uma variável `srv_addr` que armazena um endereço de socket IPv4.
   * .sin_family = AF_INET -> Indica que o endereco do soquete é um IPv4.
   * .sin_port = htons(PORT) -> Converte o número da porta de 'Host Byte Order' para 'Network Byte Order'
   * .sin_addr.s_addr: INADDR_ANY -> Vincula o soquete a todas as interfaces de rede disponíveis na máquina.
   */
  struct sockaddr_in server_address = {
    AF_INET,
    htons(PORT),
    INADDR_ANY
  };

  /*
   * -> Gepeto: Um buffer é uma área de memória temporária usada para armazenar dados
   *    enquanto eles são transferidos de uma parte do programa para outra, ou entre
   *    um programa e um dispositivo de entrada/saída.
   */
  char buffer[BUFFER_SIZE] = {0};
  const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";

  /*
   *
   */
  if((server_fd  = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("Criação do soquete falhou");
    exit(EXIT_FAILURE);
  }

  if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
    perror("Bind falhou");
    exit(EXIT_FAILURE);
  }

  if((listen(server_fd, 10) < 0)){
    perror("Listen falhou");
    exit(EXIT_FAILURE);
  }

  printf("Servidor rodando na porta %d\n", PORT);

  while (1)
  {
    printf("\tEsperando clientes se conectarem...\n");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_fd == -1)
    {
      perror("Falha na conexão com o cliente");
      exit(EXIT_FAILURE);
    }

    read(client_fd, buffer, BUFFER_SIZE);
    printf("Requisição recebida com sucesso!");

    write(client_fd, response, strlen(response));
    close(client_fd);
  }

}
