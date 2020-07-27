#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <QPainter>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QLineEdit>
#include <QTimer>
#include <pthread.h>
#include <QProcess>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <fstream>
#include <QDateTime>

#include "login.h"
#include "ui_login.h"


int password_num = 0;

char password_str[20];
char PN[9][9] = {0};


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    strcpy(PN[1], "*");
    strcpy(PN[2] , "**");
    strcpy(PN[3] , "***");
    strcpy(PN[4] , "****");
    strcpy(PN[5] , "*****");
    strcpy(PN[6] , "******");
    strcpy(PN[7] , "*******");
    strcpy(PN[8] , "********");

    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("./ui/background3.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

    ui->key_1->setDisabled(false);
    ui->key_2->setDisabled(false);
    ui->key_3->setDisabled(false);
    ui->key_4->setDisabled(false);
    ui->key_5->setDisabled(false);
    ui->key_6->setDisabled(false);
    ui->key_7->setDisabled(false);
    ui->key_8->setDisabled(false);
    ui->key_9->setDisabled(false);
    ui->login_2->setDisabled(false);

    connect(ui->key_1,SIGNAL(clicked()),this,SLOT(key0()));
    connect(ui->key_2,SIGNAL(clicked()),this,SLOT(key1()));
    connect(ui->key_3,SIGNAL(clicked()),this,SLOT(key2()));
    connect(ui->key_4,SIGNAL(clicked()),this,SLOT(key3()));
    connect(ui->key_5,SIGNAL(clicked()),this,SLOT(key4()));
    connect(ui->key_6,SIGNAL(clicked()),this,SLOT(key5()));
    connect(ui->key_7,SIGNAL(clicked()),this,SLOT(key6()));
    connect(ui->key_8,SIGNAL(clicked()),this,SLOT(key7()));
    connect(ui->key_9,SIGNAL(clicked()),this,SLOT(key8()));
    connect(ui->key_9,SIGNAL(clicked()),this,SLOT(key8()));
    connect(ui->login_2,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));

    //QPixmap a1("./ui/a1.jpg");
    //QPixmap a2("./ui/a2.jpg");
    //ui->a1->setScaledContents(true);
    //ui->a2->setScaledContents(true);
    //ui->a1->setPixmap(a1);
    //ui->a2->setPixmap(a2);
}


login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{

    //ui->user_name->setPlaceholderText('Username');
    //ui->password->setPlaceholderText('password');

    //ui->user_name->setPlainText('08117106');
    //ui->password->setPlainText('aaaaaa');

    //QString username = ui->user_name->toPlainText();
    //QString Password = ui->password->toPlainText();

    if(password_str == QString("123456"))
      {
            emit sig_login();
      }
      else
      {
         qDebug()<<"22";
         QMessageBox::warning(this, tr("warning!"), tr("User name or password error£¡"),QMessageBox::Yes);
         //ui->user_name->clear();
         ui->password->clear();
         ui->password->setFocus();

         int i;
         for(i=0; i<20;i++)
             password_str[i] = '0';

         password_num = 0;
         qDebug()<<password_num;

      }
}



void login::key0()
{
   char str[] = "0";
   strcat(password_str,str);

   password_num++ ;

   qDebug()<<password_num;
   ui->password->setPlainText(PN[password_num]);

}


void login::key1()
{
    //password_str.append('1');
    char str[] = "1";
    strcat(password_str,str);
    password_num++;
    qDebug()<<password_num;
    ui->password->setPlainText(PN[password_num]);
}


void login::key2()
{
   //password_str.append('2');
    char str[] = "2";
    strcat(password_str,str);
    password_num++;
     qDebug()<<password_num;
    ui->password->setPlainText(PN[password_num]);
}


void login::key3()
{
  //password_str.append('3');
    char str[] = "3";
    strcat(password_str,str);
    password_num++;
     qDebug()<<password_num;
    ui->password->setPlainText(PN[password_num]);
}


void login::key4()
{
    //password_str.append('4');
    char str[] = "4";
    strcat(password_str,str);
    password_num++;
     qDebug()<<password_num;
    ui->password->setPlainText(PN[password_num]);
}


void login::key5()
{
    //password_str.append('5');
    char str[] = "5";
    strcat(password_str,str);
    password_num++;
    qDebug()<<password_num;
    ui->password->setPlainText(PN[password_num]);
}


void login::key6()
{
   //password_str.append('6');
    char str[] = "6";
    strcat(password_str,str);
    password_num++;
     qDebug()<<password_num;
    ui->password->setPlainText(PN[password_num]);
}


void login::key7()
{
   // password_str.append('7');
    char str[] = "7";
    strcat(password_str,str);
    password_num++;
    ui->password->setPlainText(PN[password_num]);
}


void login::key8()
{
    //password_str.append('8');
    char str[] = "8";
    strcat(password_str,str);
    password_num++;
    ui->password->setPlainText(PN[password_num]);
}


void login::key9()
{
    //password_str.append('9');
    char str[] = "9";
    strcat(password_str,str);
    password_num++;
    ui->password->setPlainText(PN[password_num]);
}

