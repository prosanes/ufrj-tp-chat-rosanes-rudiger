#include "serverSocket.h"
#include "grupoClientes.h"
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <string>
#include<queue>

//Defines
#define MAX_MSG 256
    
//Var globais
grupoClientes clientes;
std::queue<std::string> mensagens;
sem_t mensagens_mutex;
sem_t mensagens_sinc;

//Prototipos
void* recebe_mensagem(void *socketp);
void* envia_para_todos_clientes(void *);

//Declaracoes
int main (int argc, char *argv[])
{
    printf("Usage: ./server porta\n");
    serverSocket ss(atoi(argv[1]));
    pthread_t thread_envio;

    sem_init(&mensagens_mutex,  0, 1);
    sem_init(&mensagens_sinc,   0, 0);


    ss.listenConnections();

    pthread_create( &thread_envio,
                    NULL,
                    envia_para_todos_clientes,
                    NULL);

    while(1)
    {
        client_info* client_mais_recente = new client_info;

        //Aceita conexao
        client_mais_recente->socket = ss.acceptConnection(client_mais_recente ->client_addr, client_mais_recente->socketlen);
        client_mais_recente->connected = true;

        char char_buffer[MAX_MSG];
        bzero(char_buffer,MAX_MSG);
        read(client_mais_recente->socket,char_buffer,MAX_MSG-1);
        printf("Cliente %s conectou-se\n", char_buffer);

        clientes.insere(std::string(char_buffer), client_mais_recente); 
        
        //Cria thread para receber mensages dos cliente
        pthread_create( &(client_mais_recente ->tid), NULL, 
                        recebe_mensagem, //Funcao executada pela thread
                        (void *) char_buffer); //Parametro usado pela funcao
    }

    return 0;
}

void* envia_para_todos_clientes(void *)
{
    while (1)
    {
        //Sincronizacao de mensagens
        sem_wait(&mensagens_sinc);

        sem_wait(&mensagens_mutex);
            std::string buffer = mensagens.front();
            mensagens.pop();
        sem_post(&mensagens_mutex);

        std::cout << buffer << "\n";
        clientes.enviaParaTodos(buffer);
    }

    return NULL;
}

void* recebe_mensagem(void *nome)
{
    char char_buffer[MAX_MSG];

    std::string id( (char*) nome );
    int socketfd = clientes.getSocket(id);

    while(1)
    {
        printf("Esperando msg...\n");

        bzero(char_buffer,MAX_MSG);
        if (read(socketfd,char_buffer,MAX_MSG-1) <= 0)
        {
            printf("Erro recebendo\n");
            return NULL;
        }

        if (char_buffer[0] == '\\' && char_buffer[1] == 'c')
        {
            clientes.remove(id);
            close(socketfd);
            printf("Cliente fechou conexao\n");
            return NULL;
        }

        //std::string string_buffer(char_buffer);
        std::string string_buffer = id + ": " + char_buffer;

        sem_wait(&mensagens_mutex);
            mensagens.push(string_buffer);
        sem_post(&mensagens_mutex);
        //Sincroniza mensagens
        sem_post(&mensagens_sinc);

    }

    return NULL;
}
