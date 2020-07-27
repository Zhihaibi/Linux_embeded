#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>


#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>



#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = nullptr);
    ~config();

    bool ResState;
    bool CamState;
    bool isConnect = false;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_connect_clicked();

    void server_New_Connect();

    void socket_Read_Data();

    void socket_Disconnected();

    void on_pushButton_Send_clicked();

    void sendMsg(QString msg);

private:
    Ui::config *ui;

    QTcpServer* server;
    QTcpSocket* socket;

signals:
    void sendResState(bool);
    void sendCamState(bool);
};

#endif // CONFIG_H
