#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class clientSocket
{
private:
    bool connected;
    int socketv;
    int portNum;
    char hostname[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

public:
    clientSocket(int portNum, char* hostname);
    void connectToServer(void);
    void send(char* msg);
    char* receive(void);
    void closeConnection(void);
    bool isConnected();
};

#endif
