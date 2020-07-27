#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "qt1.h"
#include "ui_qt1.h"
#include "login.h"
#include "chart.h"

Qt1 *w;
chart* adc_curve_chart;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
        adc_curve_chart = new chart();

        //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")) ;
        //app.setFont(QFont("wenquanyi", 12));
	//app.setFont(QFont("simsun", 10));

        w = new Qt1();

        QObject::connect(w, SIGNAL(sig_update_curve()), adc_curve_chart, SLOT(show()));

        w->show();

        login login_widgt;
        QObject::connect(&login_widgt, SIGNAL(sig_login()), w, SLOT(show()));
        login_widgt.show();
        QObject::connect(&login_widgt,SIGNAL(sig_login()),&login_widgt,SLOT(close()));
	return app.exec();
}
