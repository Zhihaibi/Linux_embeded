#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "config.h"

#include "monitor.h"

#include "history.h"


#include <QTcpSocket>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_configBtn_clicked();
    void on_monitorBtn_clicked();

    void showResState(bool);
    void showCamState(bool);


    void on_historyBtn_clicked();
    void getMoniMsg(QString msg);


private:
    Ui::MainWindow *ui;
    config *conf = new config;
    monitor *moni = new monitor;
    history *hist = new history;
    bool isRes = 0;
    bool isCam = 0;


signals:
    void callMonitor();
    void sendConfig(bool Res, bool Cam);
    void translationMsg(QString);
};

#endif // MAINWINDOW_H
