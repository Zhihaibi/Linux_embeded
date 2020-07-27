/********************************************************************************
** Form generated from reading UI file 'qt1.ui'
**
** Created: Tue Jul 21 21:18:17 2020
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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt1
{
public:
    QLabel *lb_time;
    QLabel *lb_adc;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *output;
    QPushButton *pb_opencamera;
    QPushButton *pb_save;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_prev;
    QPushButton *pb_next;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pb_open;
    QPushButton *pb_del;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rb_auto;
    QRadioButton *rb_manual;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox;
    QPushButton *pb_sure;
    QLabel *lb_pic;


    void setupUi(QDialog *Qt1)
    {
        if (Qt1->objectName().isEmpty())
            Qt1->setObjectName(QString::fromUtf8("Qt1"));
        Qt1->resize(480, 249);
        lb_time = new QLabel(Qt1);
        lb_time->setObjectName(QString::fromUtf8("lb_time"));
        lb_time->setGeometry(QRect(0, 0, 131, 31));

		lb_adc = new QLabel(Qt1);
		lb_adc->setObjectName(QString::fromUtf8("lb_adc"));
		lb_adc->setGeometry(QRect(250, 0, 181, 31));

        verticalLayoutWidget_2 = new QWidget(Qt1);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 156, 151, 81));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        output = new QLineEdit(verticalLayoutWidget_2);
        output->setObjectName(QString::fromUtf8("output"));

        verticalLayout_3->addWidget(output);

        pb_opencamera = new QPushButton(verticalLayoutWidget_2);
        pb_opencamera->setObjectName(QString::fromUtf8("pb_opencamera"));

        verticalLayout_3->addWidget(pb_opencamera);

        pb_save = new QPushButton(verticalLayoutWidget_2);
        pb_save->setObjectName(QString::fromUtf8("pb_save"));

        verticalLayout_3->addWidget(pb_save);

        verticalLayoutWidget = new QWidget(Qt1);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 76, 151, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pb_prev = new QPushButton(verticalLayoutWidget);
        pb_prev->setObjectName(QString::fromUtf8("pb_prev"));

        horizontalLayout_2->addWidget(pb_prev);

        pb_next = new QPushButton(verticalLayoutWidget);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));

        horizontalLayout_2->addWidget(pb_next);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pb_open = new QPushButton(verticalLayoutWidget);
        pb_open->setObjectName(QString::fromUtf8("pb_open"));

        horizontalLayout_4->addWidget(pb_open);

        pb_del = new QPushButton(verticalLayoutWidget);
        pb_del->setObjectName(QString::fromUtf8("pb_del"));

        horizontalLayout_4->addWidget(pb_del);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        rb_auto = new QRadioButton(verticalLayoutWidget);
        rb_auto->setObjectName(QString::fromUtf8("rb_auto"));

        horizontalLayout_3->addWidget(rb_auto);

        rb_manual = new QRadioButton(verticalLayoutWidget);
        rb_manual->setObjectName(QString::fromUtf8("rb_manual"));

        horizontalLayout_3->addWidget(rb_manual);


        verticalLayout->addLayout(horizontalLayout_3);

        widget = new QWidget(Qt1);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 40, 151, 31));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_5->addWidget(comboBox);

        pb_sure = new QPushButton(widget);
        pb_sure->setObjectName(QString::fromUtf8("pb_sure"));

        horizontalLayout_5->addWidget(pb_sure);

        lb_pic = new QLabel(Qt1);
        lb_pic->setObjectName(QString::fromUtf8("lb_pic"));
        lb_pic->setGeometry(QRect(160, 10, 320, 240));

        retranslateUi(Qt1);

        QMetaObject::connectSlotsByName(Qt1);
    } // setupUi

    void retranslateUi(QDialog *Qt1)
    {
        Qt1->setWindowTitle(QApplication::translate("Qt1", "Dialog", 0, QApplication::UnicodeUTF8));
        lb_time->setText(QString());
		lb_adc->setText(QString());
        output->setText(QString());
        pb_opencamera->setText(QApplication::translate("Qt1", "open camera", 0, QApplication::UnicodeUTF8));
        pb_save->setText(QApplication::translate("Qt1", "save", 0, QApplication::UnicodeUTF8));
        pb_prev->setText(QApplication::translate("Qt1", "prepic", 0, QApplication::UnicodeUTF8));
        pb_next->setText(QApplication::translate("Qt1", "nextpic", 0, QApplication::UnicodeUTF8));
        pb_open->setText(QApplication::translate("Qt1", "open", 0, QApplication::UnicodeUTF8));
        pb_del->setText(QApplication::translate("Qt1", "delete", 0, QApplication::UnicodeUTF8));
        rb_auto->setText(QApplication::translate("Qt1", "auto", 0, QApplication::UnicodeUTF8));
        rb_manual->setText(QApplication::translate("Qt1", "hand", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Qt1", "0.1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Qt1", "0.2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Qt1", "0.3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Qt1", "0.4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Qt1", "0.5", 0, QApplication::UnicodeUTF8)
        );
        pb_sure->setText(QApplication::translate("Qt1", "sure", 0, QApplication::UnicodeUTF8));
        lb_pic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Qt1: public Ui_Qt1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT1_H
