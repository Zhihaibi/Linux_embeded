#ifndef MAINPAINT_H
#define MAINPAINT_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
//#include "define.h"

#define MAPH 13
#define MAPV  14
class mapPaint : public QWidget
{    Q_OBJECT
	public:    
	explicit mapPaint(QWidget *parent = 0);    
	void paintEvent(QPaintEvent *);    
	int map_h,map_v;    
	int levelNow;    
	int stepNow;    
	int man_h,man_v;    
	int mapNow[MAPH][MAPV];    
	QPixmap *pain[19];    
	int BeginOrEnd;    
	//void paintUp_3(int x_old,int x_new);    
	//void paintUp_2(int x_old);
};
#endif 
