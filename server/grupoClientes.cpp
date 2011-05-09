#include "grupoClientes.h"

grupoClientes::grupoClientes()
{
    sem_init(&mutex, 0, 1);
}

void grupoClientes::insere(client_info* novo)
{
    sem_wait(&mutex);
        client.push_back(novo);
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

int grupoClientes::getSocket(int i)
{
    int ret = -1;
    sem_wait(&mutex);
        ret = client[i]->socket;
    sem_post(&mutex);
    return ret;
}

void grupoClientes::enviaParaTodos(std::string msg)
{
    sem_wait(&mutex);
    const char *buffer = msg.c_str();
    int size = msg.length();

    for(std::vector<client_info*>::iterator i = client.begin();
        i < client.end(); ++i)
    {
        if ((*i)->connected)
        {
            write((*i)->socket, buffer, size);
        }
    }
    sem_post(&mutex);
}

