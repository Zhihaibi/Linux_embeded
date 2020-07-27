#include "loginwin.h"
#include "ui_loginwin.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>
loginWin::loginWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginWin)
{
    ui->setupUi(this);
}

loginWin::~loginWin()
{
    delete ui;
}


void loginWin::on_pushButton_2_clicked()
{

}

void loginWin::on_loginBtn_clicked()
{
    qDebug()<<"login";
    qDebug()<<ui->userNameLEd->text();
    if(ui->userNameLEd->text().trimmed() == tr("SEU") && ui->pwdLEd->text() == tr("123456"))
    {
        qDebug()<<"11";
        /*
        MainWindow *win = new MainWindow;
        win->show();
        this->close();
        */
        quit();
    }
    else
    {
       qDebug()<<"22";
       QMessageBox::warning(this, tr("warning!"), tr("User name or password error！"),QMessageBox::Yes);
       ui->userNameLEd->clear();
       ui->pwdLEd->clear();
       ui->pwdLEd->setFocus();
    }
}
