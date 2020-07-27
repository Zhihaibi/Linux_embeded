#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>

#include "qcustomplot.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidget>
#include "QStringList"

#include <qmath.h>
#include <QTimer>
#include <QString>

#include <QFile>
#include <QFileDialog>
#include <QList>


namespace Ui {
class monitor;
}

class monitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit monitor(QWidget *parent = nullptr);
    ~monitor();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_clicked();

    void res_plot();

    void image_load();

    void on_pushButton_2_clicked();

    void getConfig(bool Res, bool Cam);

private:
    Ui::monitor *ui;
    int current_col = 0;
    int pre_col = 0;
    int num = 0;
    int camNum = 0;
    QVector<double> x;
    QVector<double> y;

    bool isRes = false;
    bool isCam = false;

signals:
    void backMain();
    void sendCamMsg(QString camMsg);
};

#endif // MONITOR_H
