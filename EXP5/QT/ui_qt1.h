/********************************************************************************
** Form generated from reading UI file 'qt1.ui'
**
** Created: Sat Jun 1 10:22:46 2019
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT1_H
#define UI_QT1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt1
{
public:
    QLabel *lb_time;
    QLabel *lb_pic;
    QLabel *label;
    QLabel *lb_num;
    QLabel *lb_sum;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_prev;
    QPushButton *pb_next;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QRadioButton *rb_manual;
    QRadioButton *rb_auto;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_del;
    QPushButton *pb_open;
    QComboBox *comboBox;

    void setupUi(QDialog *Qt1)
    {
        if (Qt1->objectName().isEmpty())
            Qt1->setObjectName(QString::fromUtf8("Qt1"));
        Qt1->resize(576, 480);
        lb_time = new QLabel(Qt1);
        lb_time->setObjectName(QString::fromUtf8("lb_time"));
        lb_time->setGeometry(QRect(190, 20, 221, 20));
        lb_pic = new QLabel(Qt1);
        lb_pic->setObjectName(QString::fromUtf8("lb_pic"));
        lb_pic->setGeometry(QRect(70, 70, 431, 261));
        label = new QLabel(Qt1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(281, 350, 16, 17));
        lb_num = new QLabel(Qt1);
        lb_num->setObjectName(QString::fromUtf8("lb_num"));
        lb_num->setGeometry(QRect(261, 350, 20, 20));
        lb_sum = new QLabel(Qt1);
        lb_sum->setObjectName(QString::fromUtf8("lb_sum"));
        lb_sum->setGeometry(QRect(290, 350, 31, 20));
        layoutWidget = new QWidget(Qt1);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(190, 390, 178, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_prev = new QPushButton(layoutWidget);
        pb_prev->setObjectName(QString::fromUtf8("pb_prev"));

        horizontalLayout->addWidget(pb_prev);

        pb_next = new QPushButton(layoutWidget);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));

        horizontalLayout->addWidget(pb_next);

        layoutWidget1 = new QWidget(Qt1);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 390, 83, 52));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rb_manual = new QRadioButton(layoutWidget1);
        rb_manual->setObjectName(QString::fromUtf8("rb_manual"));

        verticalLayout->addWidget(rb_manual);

        rb_auto = new QRadioButton(layoutWidget1);
        rb_auto->setObjectName(QString::fromUtf8("rb_auto"));

        verticalLayout->addWidget(rb_auto);

        layoutWidget2 = new QWidget(Qt1);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(190, 430, 178, 29));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_del = new QPushButton(layoutWidget2);
        pb_del->setObjectName(QString::fromUtf8("pb_del"));

        horizontalLayout_2->addWidget(pb_del);

        pb_open = new QPushButton(layoutWidget2);
        pb_open->setObjectName(QString::fromUtf8("pb_open"));

        horizontalLayout_2->addWidget(pb_open);

        comboBox = new QComboBox(Qt1);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(60, 140, 69, 22));

        retranslateUi(Qt1);

        QMetaObject::connectSlotsByName(Qt1);
    } // setupUi

    void retranslateUi(QDialog *Qt1)
    {
        Qt1->setWindowTitle(QApplication::translate("Qt1", "Dialog", 0, QApplication::UnicodeUTF8));
        lb_time->setText(QString());
        lb_pic->setText(QString());
        label->setText(QApplication::translate("Qt1", "/", 0, QApplication::UnicodeUTF8));
        lb_num->setText(QString());
        lb_sum->setText(QString());
        pb_prev->setText(QApplication::translate("Qt1", "\344\270\212\344\270\200\345\274\240", 0, QApplication::UnicodeUTF8));
        pb_next->setText(QApplication::translate("Qt1", "\344\270\213\344\270\200\345\274\240", 0, QApplication::UnicodeUTF8));
        rb_manual->setText(QApplication::translate("Qt1", "\346\211\213\345\212\250\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        rb_auto->setText(QApplication::translate("Qt1", "\350\207\252\345\212\250\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        pb_del->setText(QApplication::translate("Qt1", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        pb_open->setText(QApplication::translate("Qt1", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Qt1: public Ui_Qt1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT1_H
