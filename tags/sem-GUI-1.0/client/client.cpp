#include "clientSocket.h"
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

void* envia_mensagem(void* client_socket);
void* recebe_mensagem(void* client_socket);

int main (int argc, char *argv[])
{
    printf("Usage: ./client port server\n");
    //porta, ip
    clientSocket cs(atoi(argv[1]), argv[2]); 
    pthread_t thread_envio;

    char identificador[50];
    printf("Escreva seu identificador (sem espacos): ");
    scanf("%s", identificador);

    cs.connectToServer();

    cs.send(identificador);

    pthread_create( &thread_envio,
                    NULL,
                    envia_mensagem,
                    (void*) &cs);

    while(cs.isConnected()) 
    {
        printf("%s\n", cs.receive());
    }

    return 0;
}

void* envia_mensagem(void* client_socket)
{
    clientSocket* cs = (clientSocket*) client_socket;

    while(cs->isConnected())
    {
        char buf[256];
        scanf("%s", buf);

        cs->send(buf);

        if (buf[0] == '\\' && buf[1] == 'c')
            cs->closeConnection();
    }

    return NULL;
}

