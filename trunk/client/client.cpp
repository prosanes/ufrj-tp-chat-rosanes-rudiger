#include "clientSocket.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

void* envia_mensagem(void* client_socket);
void* recebe_mensagem(void* client_socket);

int main (int argc, char *argv[])
{
    clientSocket cs(2102, argv[1]); 
    pthread_t thread_envio;

    cs.connectToServer();

//    cs.send(argv[2]);
    pthread_create( &thread_envio,
                    NULL,
                    envia_mensagem,
                    (void*) &cs);

    while(1) 
    {
        printf("%s\n", cs.receive());
    }
    cs.closeConnection();

    return 0;
}

void* envia_mensagem(void* client_socket)
{
    clientSocket* cs = (clientSocket*) client_socket;

    while(1)
    {
        char buf[256];
        scanf("%s", buf);
        cs->send(buf);
    }

    return NULL;
}

