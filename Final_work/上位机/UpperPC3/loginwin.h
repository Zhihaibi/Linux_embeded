#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class loginWin; }
QT_END_NAMESPACE

class loginWin : public QMainWindow
{
    Q_OBJECT

public:
    loginWin(QWidget *parent = nullptr);
    ~loginWin();

private slots:
    void on_pushButton_2_clicked();
    void on_loginBtn_clicked();

private:
    Ui::loginWin *ui;

signals:
    void quit();

};
#endif // LOGINWIN_H
