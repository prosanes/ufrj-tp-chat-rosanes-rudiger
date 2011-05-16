#ifndef THREADRECEBEMSG_H
#define THREADRECEBEMSG_H

#include <QThread>
#include "clientSocket.h"

class ThreadRecebeMsg : public QThread
{
    Q_OBJECT
public:
    ThreadRecebeMsg(clientSocket* csp, QObject* mw);

protected:
    void run();

signals:
    void recebido(char*);

private:
    clientSocket* cs;
};

#endif // THREADRECEBEMSG_H
