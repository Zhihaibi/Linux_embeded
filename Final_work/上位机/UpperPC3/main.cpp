
#include "loginwin.h"
#include "mainwindow.h"
#include <QApplication>
#include "monitor.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginWin login;

    monitor moni;

    login.show();

    MainWindow *w = new MainWindow();

    QObject::connect(&login,SIGNAL(quit()),&login,SLOT(close()));
    QObject::connect(&login,SIGNAL(quit()),w,SLOT(show()));

/*
    QObject::connect(w,SIGNAL(callMonitor()),&moni,SLOT(show()));
    QObject::connect(w,SIGNAL(callMonitor()),w,SLOT(hide()));

    QObject::connect(&moni,SIGNAL(backMain()),&moni,SLOT(close()));
    QObject::connect(&moni,SIGNAL(backMain()),w,SLOT(show()));
*/

    return a.exec();
}
