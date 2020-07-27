#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conf->setWindowTitle("config");
    moni->setWindowTitle("monitor");


    QObject::connect(conf,SIGNAL(sendResState(bool)),this,SLOT(showResState(bool)));
    QObject::connect(conf,SIGNAL(sendCamState(bool)),this,SLOT(showCamState(bool)));

    QObject::connect(moni,SIGNAL(backMain()),this,SLOT(show()));
    QObject::connect(moni,SIGNAL(backMain()),moni,SLOT(hide()));

    QObject::connect(hist,SIGNAL(backMain()),this,SLOT(show()));
    QObject::connect(hist,SIGNAL(backMain()),hist,SLOT(hide()));

    QObject::connect(this,SIGNAL(sendConfig(bool,bool)),moni,SLOT(getConfig(bool,bool)));


    QObject::connect(moni,SIGNAL(sendCamMsg(QString)),this,SLOT(getMoniMsg(QString)));
    QObject::connect(this,SIGNAL(translationMsg(QString)),conf,SLOT(sendMsg(QString)));

 //   QTimer *dataTimer = new QTimer(this);

  //  connect(dataTimer, SIGNAL(timeout()), this, SLOT(on_pushButton_clicked()));
 //   dataTimer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_configBtn_clicked()
{
    conf->show();
}

void MainWindow::on_monitorBtn_clicked()
{
    callMonitor();
    moni->show();
    this->hide();
    emit sendConfig(isRes,isCam);


}

void MainWindow::showResState(bool resState)
{
    qDebug()<<"main rcs State"<<resState;
    /*
    if(resState == true)
        ui->Res->setText("1");
    else
        ui->Res->setText("0");
        */
    isRes = resState;
}
void MainWindow::showCamState(bool camState)
{
    qDebug()<<"main cam State"<<camState;
    /*
    if(camState == true)
        ui->Cam->setText("1");
    else
        ui->Cam->setText("0");
        */
    isCam = camState;
}

void MainWindow::on_historyBtn_clicked()
{
    hist->show();
    this->hide();
}

void MainWindow::getMoniMsg(QString msg)
{
    qDebug()<<msg;
    emit translationMsg(msg);
}
