#include "serverSocket.h"

serverSocket::serverSocket(int portNum)
{
    this->portNum = portNum;

    this->socketv = socket(AF_INET, SOCK_STREAM, 0);
    //Detectar erro
    //if (socketv < 0)

    //Inicializa serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->portNum);

    //Liga o socket a estrutura serv_addr
    bind(socketv, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        //Detectar erro no retorno
}

void serverSocket::listenConnections(void)
{
    listen(socketv, 5);
}

int serverSocket::acceptConnection(struct sockaddr_in& client_addr, 
                                    socklen_t& clilen)
{
    clilen = sizeof(client_addr);
    return accept(socketv, (struct sockaddr *) &client_addr, &clilen);
    //Verificar erro
}
