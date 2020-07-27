#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QTimer>
#include <QList>

namespace Ui {   //新增的
 class chart;
}

class chart:public QWidget
{
    Q_OBJECT
    Ui::chart *ui;
protected:
    void paintEvent(QPaintEvent *);
public:
    int m_count;
    float x;
    QTimer* m_Timer;
    QList<float> xList;
    QList<float> yList;


    chart(QWidget *parent = 0);
    ~chart();

public slots:
    void creatData();

};

#endif
