#ifndef HISTORY_H
#define HISTORY_H

#include <QMainWindow>
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
class history;
}

class history : public QMainWindow
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

private slots:
    void on_pushButton_clicked();
    void get_cameraList();
    void get_resistanceList();

    void on_cameraList_itemDoubleClicked(QTableWidgetItem *item);

    void on_resistanceList_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::history *ui;

signals:
    void backMain();
};

#endif // HISTORY_H
