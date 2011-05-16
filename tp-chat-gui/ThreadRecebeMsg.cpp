#include "threadRecebeMsg.h"

ThreadRecebeMsg::ThreadRecebeMsg(clientSocket* csp, QObject* mw)
    : QThread(mw)
{
    this->cs = csp;
}

void ThreadRecebeMsg::run()
{
    while(cs->isConnected())
    {
        char* received_char = cs->receive();

        printf("%s\n", received_char);

        //mw->insereTexto(received_char);
        emit recebido(received_char);
    }
}
