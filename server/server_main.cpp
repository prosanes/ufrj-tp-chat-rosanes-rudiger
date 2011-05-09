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

        client_mais_recente ->socket = ss.acceptConnection(client_mais_recente ->client_addr, client_mais_recente ->socketlen);
        client_mais_recente->connected = true;

        clientes.insere(client_mais_recente); 
        
        //Cria thread para receber mensages dos cliente
        pthread_create( &(client_mais_recente ->tid), NULL, 
                        recebe_mensagem, //Funcao executada pela thread
                        (void *) &(client_mais_recente ->socket)); //Parametro usado pela funcao
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

void* recebe_mensagem(void *socketp)
{
    char char_buffer[MAX_MSG];
    int* socketfdp = (int*) socketp;
    int socketfd = *socketfdp;

    while(1)
    {
        printf("Esperando msg...\n");

        bzero(char_buffer,MAX_MSG);
        if (read(socketfd,char_buffer,MAX_MSG-1) <= 0)
        {
            return NULL;
        }

        if (char_buffer[0] == '\\' && char_buffer[1] == 'c')
        {
            printf("Cliente fechou conexao\n");
        }

        std::string string_buffer(char_buffer);
        sem_wait(&mensagens_mutex);
            mensagens.push(string_buffer);
        sem_post(&mensagens_mutex);
        //Sincroniza mensagens
        sem_post(&mensagens_sinc);

    }

    return socketp;
}
