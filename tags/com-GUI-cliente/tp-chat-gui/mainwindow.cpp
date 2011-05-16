#include "mainwindow.h"
#include "ui_mainwindow.h"

void* recebe_mensagem(void*);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cs(2000, "localhost"),
    thread(&(this->cs), this)
{
    ui->setupUi(this);

    printf("teste\n");

    connect(ui->btn_envia, SIGNAL(clicked()), this, SLOT(slot_envia()));
    connect(ui->btn_entrar, SIGNAL(clicked()), this, SLOT(slot_entrar()));
    connect(&thread, SIGNAL(recebido(char*)), this, SLOT(slot_recebido(char*)));

    inicializa();
}

MainWindow::~MainWindow()
{
    cs.send("\\c");
    cs.closeConnection();

    thread.quit();
    thread.exit(0);


    delete ui;
}

void MainWindow::inicializa()
{
    ui->btn_envia->setVisible(false);
    ui->txt_envia->setVisible(false);
    ui->txt_recebe->setVisible(false);

}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::slot_envia()
{
    //cs.envia(ui->txt_envia->)
    QString buffer_qstr;
    buffer_qstr = ui->txt_envia->toPlainText();
    ui->txt_envia->clear();

    buffer_qstr += '\n';
    //gambiarra para enganar o compilador. Conversao de const char* pra char*
    std::string buffer_stdstr = buffer_qstr.toStdString();
    char *buffer = new char [buffer_stdstr.size()+1];
    strcpy(buffer, buffer_stdstr.c_str());

    if(cs.isConnected())
    {
        cs.send(buffer);
    }
}

void MainWindow::slot_entrar()
{
    std::string identificador_stdstr = ui->txt_nome->text().toStdString();
    ui->txt_nome->clear();

    cs.connectToServer();

    //Cria thread de receber mensagem apos se conectar
    thread.start();
    /*pthread_create(&thread_id,
                   NULL,
                   recebe_mensagem,
                   (void*) this);*/

    //gambiarra para enganar o compilador. Conversao de const char* pra char*
    char *buffer = new char [identificador_stdstr.size()+1];
    strcpy(buffer, identificador_stdstr.c_str());

    cs.send(buffer);

    ui->fr_login->setVisible(false);
    ui->fr_login->setEnabled(false);

    ui->btn_envia->setVisible(true);
    ui->txt_envia->setVisible(true);
    ui->txt_recebe->setVisible(true);
}

bool MainWindow::isConnected()
{
    return cs.isConnected();
}

char* MainWindow::receive()
{
    return cs.receive();
}

void MainWindow::insereTexto(char* texto)
{
    QString received_qstr = texto;

    ui->txt_recebe->insertPlainText(received_qstr);
}

void MainWindow::slot_recebido(char* parametro)
{
    QString received_qstr = parametro;
    ui->txt_recebe->insertPlainText(received_qstr);
}
