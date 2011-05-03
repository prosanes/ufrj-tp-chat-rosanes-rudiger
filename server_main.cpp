#include "serverSocket.h"
#include <pthread.h>
#include <vector>

void* testa_conexao(void *socketp)
{
    int* socketfdp = (int*) socketp;
    int socketfd = *socketfdp;

    while(1)
    {
        printf("Esperando msg...\n");

        char buffer[256];
        bzero(buffer,256);
        read(socketfd,buffer,255);
        printf("Here is the message: %s",buffer);

        write(socketfd,"I got your message",18);
    }

    return socketp;
}

int main (void)
{
    serverSocket ss(2101);

    pthread_t vet_thread[2];
    int vet_socket[2];
    struct sockaddr_in client_addr[2];
    socklen_t client_len[2];
    //Essas quatro estruturas a cima (os elemento, não os vetores)
    //formam as informacoes do cliente. Talvez seja uma boa criar uma
    //classe para encapsular tudo isso.

    ss.listenConnections();

    for(int i = 0; i < 2; i++)
    {
        vet_socket[i] = ss.acceptConnection(client_addr[i], client_len[i]);
        pthread_create( &vet_thread[i], NULL, testa_conexao, 
                        (void *) &vet_socket[i]);
    }

    for (int i = 0; i < 2; i++)
        pthread_join( vet_thread[i], NULL);

    return 0;
}


