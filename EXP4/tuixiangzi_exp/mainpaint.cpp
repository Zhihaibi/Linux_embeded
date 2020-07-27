// MAPPAINT_H 
#include <QPainter>
#include <QDebug>
#include "mainpaint.h"

mapPaint::mapPaint(QWidget *parent) :    QWidget(parent)
{    
	qDebug()<<"mappaint mappaint";
	map_h=MAPH*15;    
	map_v=MAPV*15;    

	qDebug()<<"mappaint mappaint"<<"h="<<map_h<<"v="<<map_v;
	setMinimumSize(map_h,map_v);
	pain[0]=new QPixmap("./game/0000.png");    
	pain[1]=new QPixmap("./game/0001.png");    
	pain[2]=new QPixmap("./game/0010.png");    
	pain[3]=new QPixmap("./game/0011.png");    
	pain[4]=new QPixmap("./game/0100.png");    
	pain[5]=new QPixmap("./game/0101.png");    
	pain[6]=new QPixmap("./game/box.png");    
	pain[7]=new QPixmap("./game/0111.png");    
	pain[8]=new QPixmap("./game/1000.png");    
	pain[9]=new QPixmap("./game/goal.png");    
	pain[10]=new QPixmap("./game/1010.png");    
	pain[11]=new QPixmap("./game/1011.png");    
	pain[12]=new QPixmap("./game/1100.png");    
	pain[13]=new QPixmap("./game/1101.png");    
	pain[14]=new QPixmap("./game/1110.png");    
	pain[15]=new QPixmap("./game/1111.png");    
	pain[16]=new QPixmap("./game/ground.png");    
	pain[17]=new QPixmap("./game/get.png");    
	pain[18]=new QPixmap("./game/man.png");
}
void mapPaint::paintEvent(QPaintEvent *)
{    
	QPainter p(this);    
	p.translate(0,map_v);  
	qDebug()<<"level"<<levelNow;
	if(levelNow==0)    
	{        
		if(BeginOrEnd==-1)        
		{            
			QPixmap begin("./game/.png");            
			p.drawPixmap(0,-map_v,begin);        
		}        
		if(BeginOrEnd==1)        
		{            
			QPixmap end("./game/.png");            
			p.drawPixmap(0,-map_v,end);        
		}    
	}    
	else    
	{        
		int i,j;       
		for(i=0;i<MAPH;i++)            
			for(j=0;j<MAPV;j++)            
			{                
				QPixmap l=*pain[mapNow[i][j]];     
				p.drawPixmap(i*15,-j*15,l);            
			}    
	}
}
