#include "config.h"
#include "ui_config.h"
#include <QDebug>

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);

    ui->lineEdit_Port->setText("8765");
//    ui->pushButton_Send->setEnabled(false);
    server = new QTcpServer();
    //连接信号槽
    connect(server,&QTcpServer::newConnection,this,&config::server_New_Connect);

}

config::~config()
{
    delete ui;
}

void config::on_pushButton_2_clicked()
{
    if(CamState == true &&isConnect == true)
    {
        QString msg = "start";
         socket->write(msg.toLatin1());
         socket->flush();

    }
    this->hide();
}

void config::on_pushButton_clicked()
{
    qDebug()<<"STATE";
    qDebug()<<"rcs State"<<ui->resCB->checkState();
    qDebug()<<"cam State"<<ui->camCB->checkState();
    ResState = ui->resCB->checkState() == Qt::Checked ? true : false;
    CamState = ui->camCB->checkState() == Qt::Checked ? true : false;
    qDebug()<<"rcs State"<<ResState;
    qDebug()<<"cam State"<<CamState;
    emit sendResState(ResState);
    emit sendCamState(CamState);

    this->close();
}

void config::on_connect_clicked()
{
    if(ui->connect->text() == tr("Connect"))
        {
            //从输入框获取端口号
            int port = ui->lineEdit_Port->text().toInt();

            //监听指定的端口
            if(!server->listen(QHostAddress::Any, port))
            {
                //若出错，则输出错误信息
                qDebug()<<server->errorString();
                return;
            }
            //修改按键文字
            ui->connect->setText("Disconnect");
            qDebug()<< "Listen succeessfully!";

        }
        else
        {
    /*
            //如果正在连接（点击侦听后立即取消侦听，若socket没有指定对象会有异常，应修正——2017.9.30）
            if(socket->state() == QAbstractSocket::ConnectedState)
            {
                //关闭连接
                socket->disconnectFromHost();
            }
    */
            socket->abort();
            //取消侦听
            server->close();
            //修改按键文字
            ui->connect->setText("Connect");
            ui->lineEdit_Success->setText("no connection");
            //发送按键失能
 //           ui->pushButton_Send->setEnabled(false);
        }




}



void config::on_pushButton_Send_clicked()
{
  //  qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
        //获取文本框内容并以ASCII码形式发送
  //      socket->write(ui->textEdit_Send->toPlainText().toLatin1());
        socket->flush();
}

void config::sendMsg(QString msg)
{
    qDebug()<<"send:"<<msg;
    if(isConnect)
    {
        socket->write(msg.toLatin1());
        socket->flush();
    }
    else {
        qDebug()<<"no connect client";
    }
}


void config::server_New_Connect()
{
    //获取客户端连接
    socket = server->nextPendingConnection();
    //连接QTcpSocket的信号槽，以读取新数据
    QObject::connect(socket, &QTcpSocket::readyRead, this, &config::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &config::socket_Disconnected);
    //发送按键使能
//    ui->pushButton_Send->setEnabled(true);
    isConnect = true;
    ui->lineEdit_Success->setText("Success");
    qDebug() << "A Client connect!";
}

void config::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->textEdit_Recv->toPlainText();
        str+=tr(buffer);
        //刷新显示
        ui->textEdit_Recv->setText(str);
    }
}

void config::socket_Disconnected()
{
    //发送按键失能
//    ui->pushButton_Send->setEnabled(false);
    isConnect = false;
    qDebug() << "Disconnected!";
}


