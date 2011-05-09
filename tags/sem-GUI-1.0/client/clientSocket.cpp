#include "clientSocket.h"

clientSocket::clientSocket(int portNum, char* hostname)
{
    this->connected = false;

    this->portNum = portNum;

    int i;
    for (i = 0; hostname[i] != '\0' && i < 256; i++)
        this->hostname[i] = hostname[i];
    this->hostname[i] = '\0';

    this->socketv = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketv == 0)
        printf("erro socket\n");

    this->server = gethostbyname(this->hostname);
    if (this->server == NULL)
        printf("No such host\n");
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr,
          (char*)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(this->portNum);

}

void clientSocket::connectToServer(void)
{
    if (connected)
    {
        printf("Tentando conectar sem estar conectado\n");
        return;
    }

    if (connect(socketv,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("ERROR connecting\n");
        connected = false;
        return ;
    }

    connected = true;
}

void clientSocket::send(char* msg)
{
    if (!connected)
    {
        printf("Tetando enviar sem estar conectado\n");
        return;
    }

    if( write(socketv,msg,strlen(msg)) < 0)
        printf("ERROR escrevendo\n");
}

char* clientSocket::receive(void)
{
    if (!connected)
    {
        printf("Tentando receber sem estar conectado\n");
        return NULL;
    }

    int size = read(socketv,buffer,255);
    if (size < 0)
        printf("ERROR recebendo\n");
    else
        buffer[size] = '\0';

    return buffer;
}

void clientSocket::closeConnection(void)
{
    if (!connected)
        return;
    connected = false;
    close(socketv);
}

bool clientSocket::isConnected()
{
    return connected;
}
