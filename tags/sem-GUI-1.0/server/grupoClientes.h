#ifndef __GRUPOCLIENTES_H__
#define __GRUPOCLIENTES_H__

#include <pthread.h>
#include <semaphore.h>
#include <map>
#include <string>
#include "serverSocket.h"

struct client_info
{
    pthread_t tid;
    int socket;
    struct sockaddr_in client_addr;
    socklen_t socketlen;
    bool connected;
};

class grupoClientes
{
private:
    std::map<std::string, client_info*> client;
    sem_t mutex;
    
public:
    grupoClientes();
    void insere(std::string, client_info*);
    int size();
    int getSocket(std::string id);
    void enviaParaTodos(std::string msg);
    void remove(std::string id);
};
    

#endif
