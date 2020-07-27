#include "chart.h"
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <qmath.h>
//#include "uidemo18.h"
//#include "ui_chart.h"
#include <qfiledialog.h>
#include <QDateTime>
#include <QScreen>
#include <qmessagebox.h>
#include <QDebug>
#include "qt1.h"

extern int pub_adc_peroid;
int pub_adc = 0;
extern int adc_value;

chart::chart(QWidget *parent) : QWidget(parent)
{
    //this->setFixedHeight(249);
    //this->setFixedWidth(480);
    //this->showFullScreen();
    x = -10;
    m_count = 0;
    m_Timer = new QTimer(this);
    m_Timer->start();
    m_Timer->setInterval(100);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(creatData()));
    xList.clear();
    yList.clear();

}

void chart::creatData()
{
    m_Timer->setInterval(pub_adc_peroid);
    x += 2;
    m_count += 1;
    //qDebug()<<QString("adc:%1").arg(adc_value);
    if(m_count%2)
    {
        xList.append(x);
        yList.append((float)(10000-adc_value)/1000*4-20); //t -> adc_value 1000->10000
    }
    else
    {
        xList.append(x);
        yList.append((float)(10000-adc_value)/1000*4-20);
        update();
    }

    if(m_count == 100)
    {

        QString filePathName = "./historyR/R-";
        QPixmap pixmap = QPixmap::grabWidget(this);
        filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");

        filePathName += ".jpg";

        if(!pixmap.save(filePathName))
        {
            QMessageBox::information(this,"SCreen shot","SCreen shot false！");
        }

        xList.clear();
        yList.clear();
        m_count = 0;
        x = -100;
    }
}


void chart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(0.4);
    painter.setPen(pen);
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(-100, -20, 200, 40); // (-10, 2)    (10, -2)
    painter.fillRect(-100, -20, 200, 40, Qt::white);

    int Xline = -100;
    for(int i=1;i<=10;i++)//分成10份
    {
        painter.drawLine(QPointF(Xline, 18.5), QPointF(Xline+20, 18.5));
        painter.drawLine(QPointF(Xline, 18.3), QPointF(Xline, 18.7));
        Xline+=20;
    }
    int Yline = -20;
    for(int i=1;i<=10;i++)//分成10份
    {
        painter.drawLine(QPointF(-98, Yline), QPointF(-98, Yline+4));
        painter.drawLine(QPointF(-99, Yline), QPointF(-97, Yline));
        Yline+=4;
    }



    QFont font("Microsoft YaHei",3,QFont::Normal ,true);
    painter.setFont(font);
    painter.setPen(Qt::red);
    painter.drawText(Xline,15,QString::number((int)(Xline)));


    painter.drawText(75,18,tr("TIME / t*5"));
    painter.drawText(-90,-17,tr("LEVEL /K"));
    painter.drawText(-95,-18,tr("10"));
    painter.drawText(-95,-14.5,tr("9"));
    painter.drawText(-95,-11,tr("8"));
    painter.drawText(-95,-6.8,tr("7"));
    painter.drawText(-95,-3,tr("6"));
    painter.drawText(-95,1.1,tr("5"));
    painter.drawText(-95,5,tr("4"));
    painter.drawText(-95,9,tr("3"));
    painter.drawText(-95,13,tr("2"));
    painter.drawText(-95,17,tr("1"));

    pen.setColor(Qt::yellow);

    pen.setWidthF(0.4);
    painter.setPen(pen);


    for(int i = 0; i < yList.count(); i++)
    {
        if(i == 0)
            painter.drawPoint(QPointF(xList[i], yList[i]));
        else
            painter.drawLine(QPointF(xList[i-1], yList[i-1]), QPointF(xList[i], yList[i]));
    }
}


chart::~chart()
{

}
