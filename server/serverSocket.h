#ifndef __SERVERSOCKET_H__
#define __SERVERSOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

class serverSocket
{
private:
    int socketv;
    int portNum;
    struct sockaddr_in serv_addr;

public:
    serverSocket(int portNum);
    void listenConnections(void);
    int acceptConnection(struct sockaddr_in& client_addr, socklen_t& clilen);


};

#endif
