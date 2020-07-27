#include "monitor.h"
#include "ui_monitor.h"

#define PERIOD_NUM 8

monitor::monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::monitor)
{
    ui->setupUi(this);

    //plot config
    ui->plot->plotLayout()->insertRow(0);
    ui->plot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->plot, "Statistical Graph of Resistance", QFont("微软雅黑",12, QFont::Bold)));


    // set dark background gradient设置暗背景梯度:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(200, 150, 220));
    gradient.setColorAt(0.56, QColor(200, 150, 200));
    gradient.setColorAt(1, QColor(220, 150, 200));
    ui->plot->setBackground(QBrush(gradient));

    // create empty bar chart objects创建三个空的条形图对象:
    QCPBars *LoveTime = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);//阻值历史数据
    QCPBars *LoveTimes = new QCPBars(ui->plot->xAxis, ui->plot->yAxis2);//阻值现在数据
    //将LatencyTime和ErrorTimes并排显示
//    QCPBarsGroup *group = new QCPBarsGroup(ui->plot);
//    LoveTime->setBarsGroup(group);
//    LoveTimes->setBarsGroup(group);
    //设置抗锯齿
    LoveTime->setAntialiased(false); // gives more crisp, pixel aligned bar borders:提供更清晰，像素对齐的条形边框
    LoveTimes->setAntialiased(false);
    //设置叠加差距
    //LatencyTime->setStackingGap(1);
    //ErrorTimes->setStackingGap(1);
    //fossil->setStackingGap(1);
    // set names and colors设置名称和颜色:
    LoveTimes->setWidth(0.3);//设置宽度
    //ErrorTimes->setWidthType("wtPlotCoords");//wtAbsolute:wtAxisRectRatio:wtPlotCoords设置宽度
    LoveTimes->setName("Current");
    LoveTimes->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    LoveTimes->setBrush(QColor(0, 168, 140));
    LoveTime->setWidth(0.3);//设置宽度
    //LatencyTime->setWidthType("wtPlotCoords");//wtAbsolute:wtAxisRectRatio:wtPlotCoords设置宽度
    LoveTime->setName("History");
    LoveTime->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    LoveTime->setBrush(QColor(250, 170, 20));
    // stack bars on top of each other把一个Bar叠加在另外一个Bar上面
    //ErrorTimes->moveAbove(fossil);
    //LatencyTime->moveAbove(ErrorTimes);

    //绘制xAxis
    QVector<double> ticks;
    QVector<QString> labels;
 //   ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<<8<<9<<10<<11<<12;
  //  labels << "1st" << "2nd" << "3rd" << "4th" << "5th" << "6th" << "7th"<<"8th";

    for(int index = 1; index<=PERIOD_NUM; index++)
    {
        ticks  << index ;
        labels << QString::number(index);

    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    //textTicker->addTicks(ticks, labels);

  //  ui->plot->xAxis->setTicker(textTicker);//设置刻度标记CH
    ui->plot->xAxis->setTickLabelRotation(60);//设置刻度标签旋转
    ui->plot->xAxis->setSubTicks(false);//设置是否显示子刻度线
    ui->plot->xAxis->setTickLength(0, 0.001);//设置标记的长度
    ui->plot->xAxis->setRange(0, PERIOD_NUM);//设置范围
    ui->plot->xAxis->setBasePen(QPen(Qt::white));//设置轴基线颜色
    ui->plot->xAxis->setTickPen(QPen(Qt::white));//设置刻度颜色
    ui->plot->xAxis->grid()->setVisible(true);//网格可视
    ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));//网格虚线
    ui->plot->xAxis->setTickLabelColor(Qt::white);//设置刻度标签颜色
    ui->plot->xAxis->setLabelColor(Qt::white);//设置轴标签的颜色

    // 绘制yAxis:
    ui->plot->yAxis->setRange(0, 10000);//设置轴范围的下限和上限
    ui->plot->yAxis->setPadding(5); // 设置轴的填充a bit more space to the left border：在左边边界多留一点空间
    ui->plot->yAxis->setLabel("Resistence");
    ui->plot->yAxis->setBasePen(QPen(Qt::white));//设置轴基线颜色
    ui->plot->yAxis->setTickPen(QPen(Qt::white));//设置刻度线颜色
    ui->plot->yAxis->setSubTickPen(QPen(Qt::white));//设置子刻度线颜色
    ui->plot->yAxis->grid()->setSubGridVisible(true);//设置子网格可视
    ui->plot->yAxis->setTickLabelColor(Qt::white);//设置刻度标签颜色
    ui->plot->yAxis->setLabelColor(Qt::white);//设置轴标签的颜色
    ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));//设置网格颜色和线型，网格实线
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));//设置子网格颜色和线型，网格虚线

    // Add data添加数据:
    QVector<double> LoveTimesData, LoveTimeData;
    LoveTimeData  << 1000 << 3000 << 3430 << 2778 << 4356 << 8788 << 4345<<5555;
//    LoveTime->setData(ticks, LoveTimeData);
    QVector<double> ticks_1;
    ticks_1<<8;
    LoveTimesData << 1000/double(2000);
 //   LoveTimes->setData(ticks_1, LoveTimesData);//将容器内数据添加到对应刻度的点上，数量应相同
/*
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setAntialiasedFill(false);
    qDebug()<<ticks<<LoveTimeData;
    ui->plot->graph(0)->setData(ticks, LoveTimeData);
    */
    QTimer *dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(res_plot()));
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(image_load()));
    dataTimer->start(1000);
}

monitor::~monitor()
{
    delete ui;
}

void monitor::on_tabWidget_tabBarClicked(int index)
{

}

void monitor::res_plot()
{
    //qDebug()<<"here";
    if(isRes == true)
    {
        ui->res_update->setText("Updating");
        current_col = 0;

        QString path = "/home/oym/myQT/UpperPC3/test.txt";
        QFile file(path);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            qDebug()<<"error!";
        }

        QTextStream in(&file);

        QString last_line, current_line = in.readLine();

        while (!current_line.isNull())
        {
            current_line = in.readLine();
            if(!current_line.isNull())
                last_line = current_line;
            current_col++;
        }
       // qDebug()<<"pre_col:"<<pre_col<<"current_col"<<current_col;
        //qDebug()<<last_line;


        if(pre_col != current_col)
        {
            num++;

            if(num>PERIOD_NUM)               //one period
            {
                num = 1;
                x.clear();
                y.clear();

                QString saveDirPath = "/home/oym/myQT/UpperPC3/resistanceHistory/";

                QDateTime current_date_time =QDateTime::currentDateTime();
                QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");

                QString path = saveDirPath+current_date+'.png';
                ui->plot->savePng(path);

            }

            ui->lineEdit_res->setText(last_line);

            float data = last_line.toFloat();
            if(data<1000)
                ui->lineEdit_state->setText("Low");
            else if(data>9000)
            {
                ui->lineEdit_state->setText("High");
            }
            else {
                ui->lineEdit_state->setText("Normal");
            }

           // qDebug()<<"data:"<<data<<"last_line:"<<last_line;
            x<<num;
            y<<data;
            ui->plot->replot();
            ui->plot->addGraph();
            ui->plot->graph(0)->setPen(QPen(Qt::blue));
            ui->plot->graph(0)->setAntialiasedFill(false);
          //  qDebug()<<"x:"<<x;
          //  qDebug()<<"y:"<<y;
            ui->plot->graph(0)->setData(x, y);
        }
        pre_col = current_col;
    }
    else {
        ui->res_update->setText("No update");
    }






}

void monitor::image_load()
{
    if(isCam == true)
    {
        ui->cam_update->setText("Updating");
        QStringList imageList;
        QString dirPath = "/home/oym/myQT/UpperPC3/Images/";
        QDir dir(dirPath);
        if(!dir.exists())
        {
            qDebug()<<"dirpath is not exist..";
            return;
        }
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QStringList filters;
        filters<<"*.bmp"<<"*.jpg";
        dir.setNameFilters(filters);
        imageList = dir.entryList();
        //qDebug()<<imageList;
        int size = imageList.size();
        //qDebug()<<"size:"<<size;

        //qDebug()<<imageList.at(size-1);

        //
        QString imgIndex = imageList.at(size-2);

        QString imagePath = dirPath + imgIndex;

        //qDebug()<<imagePath;

        QImage image;
        if(image.load(imagePath) && camNum!=size)
        {
            ui->image->setPixmap(QPixmap::fromImage(image));
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
            ui->lineEdit_time->setText(current_date);

            QString camMsg ="get a photo";
            emit sendCamMsg(camMsg);
        }
        camNum = size;
    }
    else
    {
        ui->cam_update->setText("No update");
    }

}

void monitor::on_pushButton_clicked()
{
    backMain();
}

void monitor::on_pushButton_2_clicked()
{
    /*
    QString imagePath = "/home/oym/myQT/UpperPC3/Images/img1.jpg";
    QImage image;
    if(image.load(imagePath))
    {
        ui->image->setPixmap(QPixmap::fromImage(image));
    }
    */
    QStringList imageList;
    QString dirPath = "/home/oym/myQT/UpperPC3/Images/";
    QDir dir(dirPath);
    if(!dir.exists())
    {
        qDebug()<<"dirpath is not exist..";
        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters<<"*.bmp"<<"*.jpg";
    dir.setNameFilters(filters);
    imageList = dir.entryList();
    qDebug()<<imageList;
    int size = imageList.size();
    qDebug()<<"size:"<<size;

    qDebug()<<imageList.at(size-1);

    QString imgIndex = imageList.at(size-1);

    QString imagePath = dirPath + imgIndex;

    qDebug()<<imagePath;

    QImage image;
    if(image.load(imagePath))
    {
        ui->image->setPixmap(QPixmap::fromImage(image));
    }

}

void monitor::getConfig(bool Res, bool Cam)
{
    isRes = Res;
    isCam = Cam;
    qDebug()<<"Res:"<<isRes<<"Cam:"<<isCam;

}
