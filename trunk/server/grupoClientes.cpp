#include "grupoClientes.h"

grupoClientes::grupoClientes()
{
    sem_init(&mutex, 0, 1);
}

void grupoClientes::insere(std::string id, client_info* cliente)
{
    sem_wait(&mutex);
        while (client.find(id) != client.end())
        {
            id += '0';
        }
        client[id] = cliente;
    sem_post(&mutex);
}

int grupoClientes::size()
{
    int ret = 0;
    sem_wait(&mutex);
        ret = client.size();
    sem_post(&mutex);
    return ret;
}

int grupoClientes::getSocket(std::string id)
{
    int ret = -1;
    sem_wait(&mutex);
        if (client.find(id) != client.end())
        {
            ret = client[id]->socket;
        }
    sem_post(&mutex);
    return ret;
}

void grupoClientes::enviaParaTodos(std::string msg)
{
    sem_wait(&mutex);
    const char *buffer = msg.c_str();
    int size = msg.length();

    std::map<std::string, client_info*>::iterator i;
    for(i = client.begin(); i != client.end(); ++i)
    {
        client_info* client_atual = (*i).second;
        write(client_atual->socket, buffer, size);
    }
    sem_post(&mutex);
}

void grupoClientes::remove(std::string id)
{
    sem_wait(&mutex);
        client.erase(id);
    sem_post(&mutex);
}

