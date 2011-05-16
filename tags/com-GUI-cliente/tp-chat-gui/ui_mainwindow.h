/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 15 17:07:27 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *txt_envia;
    QPlainTextEdit *txt_recebe;
    QPushButton *btn_envia;
    QFrame *fr_login;
    QLineEdit *txt_nome;
    QPushButton *btn_entrar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(319, 400);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        txt_envia = new QPlainTextEdit(centralWidget);
        txt_envia->setObjectName(QString::fromUtf8("txt_envia"));
        txt_envia->setGeometry(QRect(10, 240, 191, 84));
        txt_recebe = new QPlainTextEdit(centralWidget);
        txt_recebe->setObjectName(QString::fromUtf8("txt_recebe"));
        txt_recebe->setGeometry(QRect(10, 10, 301, 221));
        txt_recebe->setReadOnly(true);
        btn_envia = new QPushButton(centralWidget);
        btn_envia->setObjectName(QString::fromUtf8("btn_envia"));
        btn_envia->setGeometry(QRect(210, 240, 101, 81));
        fr_login = new QFrame(centralWidget);
        fr_login->setObjectName(QString::fromUtf8("fr_login"));
        fr_login->setGeometry(QRect(60, 50, 211, 141));
        fr_login->setFrameShape(QFrame::StyledPanel);
        fr_login->setFrameShadow(QFrame::Raised);
        txt_nome = new QLineEdit(fr_login);
        txt_nome->setObjectName(QString::fromUtf8("txt_nome"));
        txt_nome->setGeometry(QRect(20, 20, 171, 31));
        btn_entrar = new QPushButton(fr_login);
        btn_entrar->setObjectName(QString::fromUtf8("btn_entrar"));
        btn_entrar->setGeometry(QRect(20, 60, 171, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 319, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btn_envia->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        btn_entrar->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
