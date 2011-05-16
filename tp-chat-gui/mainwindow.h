#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientSocket.h"
#include "threadRecebeMsg.h"
#include <string>
#include <string.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isConnected();
    char* receive();
    void insereTexto(char*);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    clientSocket cs;
    ThreadRecebeMsg thread;

    void inicializa();

private slots:
    void slot_envia();
    void slot_entrar();
    void slot_recebido(char*);
    
};

#endif // MAINWINDOW_H
