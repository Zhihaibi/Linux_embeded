#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <QString>
#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QProcess>
#include <QTimer>
#include <QImage>
#include <QDebug>


void Send_img(QString filepath);
void Send_R(int AD_value);
char *int_to_string(int num);
void receive_msg();
void connect();

#endif COMMUNICATE_H
