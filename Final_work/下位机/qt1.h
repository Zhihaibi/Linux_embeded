#ifndef QT1_H
#define QT1_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QProcess>
#include <QTimer>
#include <QImage>
#include "camera.h"
#include "ui_qt1.h"
#include "adc.h"


//#include "dlinklist.h"
void Is_Same();
char *int_to_string2(int num);

class Qt1: public QDialog,public Ui_Qt1
{
	Q_OBJECT
public:
	Qt1(QWidget *parent = 0);
	~Qt1();
	void strip(char *s);
	int judge(char *s);
    void showCapPhoto();
//	void insert_dlinklist(DLIST *d,char *s);

signals:
//	mysig();
    void sig_update_curve();
	
public slots:
    void time_s();
    void Time_change();
    void fun_time();
    void fun_pic();
    void fun_cntl();
    void display_pic();
    void fun_prev();
    void fun_delete();
    void fun_open();
    void fun_cap_open();
    void fun_take_photo();
    void fun_refresh_pic();
    void fun_refresh_label();
    void show_adc();
    void fun_communicate();
    void fun_chart();
    void fun_send_img();
    //void fun_send_R();
    //int OnBtnOK();
	
private:
        QTimer t1;
        QTimer t2;
        QTimer t3;
        QTimer t4;
        QTimer adc_timer;
        QTimer img_timer;

        int len;
        bool isCapOpen;
        Camera* myCamera;
        int width;
        int height;
        QImage* m_image;
        unsigned char *frameBufRGB;
        unsigned char *frameBufYUV;
        bool isToSave;
        void fun_clean_pixmap();
        void InitBox();

};


#endif 
