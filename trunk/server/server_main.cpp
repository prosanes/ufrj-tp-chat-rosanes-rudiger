#include "serverSocket.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <string>
#include<queue>

//Defines
#define MAX_MSG 256

//Estruturas
struct client_info
{
    pthread_t tid;
    int socket;
    struct sockaddr_in client_addr;
    socklen_t socketlen;
};
    
//Var globais
std::vector<client_info*> clients;
std::queue<std::string> mensagens;
sem_t clients_mutex;
sem_t mensagens_mutex;
sem_t mensagens_sinc;

//Prototipos
void* recebe_mensagem(void *socketp);
void* envia_para_todos_clientes(void *);

//Declaracoes
int main (void)
{
    serverSocket ss(2101);
    pthread_t thread_envio;

    sem_init(&clients_mutex,    0, 1);
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

        sem_wait(&clients_mutex);
            clients.push_back(client_mais_recente );
        sem_post(&clients_mutex);
        
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

        sem_wait(&clients_mutex);
            int clients_size = clients.size();
        sem_post(&clients_mutex);

        sem_wait(&mensagens_mutex);
            bool empty = mensagens.empty();
        sem_post(&mensagens_mutex);

        while(!empty)
        {
            sem_wait(&mensagens_mutex);
                const char* buffer = mensagens.front().c_str();
                int buffer_size = mensagens.front().length();
                mensagens.pop();
                empty = mensagens.empty();
            sem_post(&mensagens_mutex);

            std::cout << buffer << "\n";
            for (int i = 0; i < clients_size; ++i)
            {
                sem_wait(&clients_mutex);
                    int socket_atual = clients[i]->socket;
                sem_post(&clients_mutex);

                write(socket_atual, buffer, buffer_size);
            }

        }
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
        read(socketfd,char_buffer,MAX_MSG-1);

        std::string string_buffer(char_buffer);
        sem_wait(&mensagens_mutex);
            mensagens.push(string_buffer);
        sem_post(&mensagens_mutex);
        //Sincroniza mensagens
        sem_post(&mensagens_sinc);

    }

    return socketp;
}
