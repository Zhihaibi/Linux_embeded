#include "history.h"
#include "ui_history.h"

#include <QDebug>

history::history(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);

    ui->cameraList->setColumnCount(1);//设置列数
    ui->cameraList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cameraList->setRowCount(30);//设置行数
    ui->cameraList->setWindowTitle("QTableWidget");
    QStringList m_Header;
    m_Header<<QString("camera history");
    ui->cameraList->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->cameraList->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->cameraList->horizontalHeader()->setVisible(true);//横向表头可视化
    //ui->tableWidget->setShowGrid(false);//隐藏栅格
    ui->cameraList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->cameraList->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->cameraList->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->cameraList->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色


    ui->resistanceList->setColumnCount(1);//设置列数
    ui->resistanceList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->resistanceList->setRowCount(30);//设置行数
    ui->resistanceList->setWindowTitle("QTableWidget");
    QStringList m_Header2;
    m_Header2<<QString("name");
    ui->resistanceList->setHorizontalHeaderLabels(m_Header2);//添加横向表头
    ui->resistanceList->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->resistanceList->horizontalHeader()->setVisible(true);//横向表头可视化
    //ui->tableWidget->setShowGrid(false);//隐藏栅格
    ui->resistanceList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->resistanceList->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->resistanceList->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->resistanceList->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色


    QTimer *dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(get_cameraList()));
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(get_resistanceList()));
    dataTimer->start(1000);

}

history::~history()
{
    delete ui;
}

void history::on_pushButton_clicked()
{
    backMain();
}
void history::get_cameraList()
{
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
    for(int i = 0; i< size; i++)
    {
        ui->cameraList->setRowHeight(i, 30);
        ui->cameraList->setItem(i, 0, new QTableWidgetItem(dirPath+imageList.at(i)));
       // usleep(100);
        ui->cameraList->item(i, 0)->setTextAlignment(Qt::AlignLeft);//居左显示
        ui->cameraList->item(i, 0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
        ui->cameraList->item(i, 0)->setTextColor(QColor(0,0,0));//设置文本颜色
        ui->cameraList->item(i, 0)->setFont(QFont("Helvetica"));//设置字体为黑体
    }


}

void history::get_resistanceList()
{

    QStringList imageList;
    QString dirPath = "/home/oym/myQT/UpperPC3/resistanceHistory/";
    QDir dir(dirPath);
    if(!dir.exists())
    {
        qDebug()<<"dirpath is not exist..";
        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
 //   QStringList filters;
 //   filters<<"*.bmp"<<"*.jpg";
 //   dir.setNameFilters(filters);
    imageList = dir.entryList();
    //qDebug()<<imageList;
    int size = imageList.size();
    for(int i = 0; i< size; i++)
    {
        ui->resistanceList->setRowHeight(i, 30);
        ui->resistanceList->setItem(i, 0, new QTableWidgetItem(dirPath+imageList.at(i)));
        ui->resistanceList->item(i, 0)->setTextAlignment(Qt::AlignLeft);//居左显示
        ui->resistanceList->item(i, 0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
        ui->resistanceList->item(i, 0)->setTextColor(QColor(0,0,0));//设置文本颜色
        ui->resistanceList->item(i, 0)->setFont(QFont("Helvetica"));//设置字体为黑体
    }


}

void history::on_cameraList_itemDoubleClicked(QTableWidgetItem *item)
{
    //qDebug()<<item->text();
    QString itemPath = item->text();
    QImage image;
    if(image.load(itemPath))
    {
        ui->cameraHistory->setPixmap(QPixmap::fromImage(image));
    }
}

void history::on_resistanceList_itemDoubleClicked(QTableWidgetItem *item)
{
    //qDebug()<<item->text();
    QString itemPath = item->text();
    QImage image;
    if(image.load(itemPath))
    {
        ui->resistanceHistory->setPixmap(QPixmap::fromImage(image));
    }
}
