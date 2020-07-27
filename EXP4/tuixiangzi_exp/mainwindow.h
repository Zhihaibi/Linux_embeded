#ifndef MAINWINDOW_H 
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QSpacerItem>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSound>
#include <QTimer>
#include <QPushButton>
#include "mainpaint.h"
//#include "define.h"
//#include "choosedlg.h"
//class mapPaint;


#define Q0000 	0
#define Q0001 	1
#define Q0010 	2
#define Q0011 	 3
#define Q0100 	4
#define Q0101 	5
#define  BOX    6 //箱子
#define Q0111 	7
#define Q1000 	8
#define GOAL 	 9
#define Q1010 	10
#define Q1011 	11
#define Q1100 	12
#define Q1101  	13
#define Q1110 	14
#define Q1111 	15
#define GROUND 	16
#define  GET 		17
#define  MAN 	18


#define MAPH 13
#define MAPV  14


class MainWindow : public QMainWindow
{    
	Q_OBJECT
public:    
	 MainWindow(QWidget *parent = 0);
	 ~MainWindow();
	//*******************²Ëµ¥À¸************************    
	QMenu *gameMenu;//ÓÎÏ·²Ëµ¥    
	QMenu *musicMenu;//ÒôÀÖ²Ëµ¥    
	QMenu *helpMenu;//°ïÖú    
	QAction *beginGameAction;//¿ªÊ¼ÓÎÏ·    
	QAction *chooseGameAction;//Ñ¡Ôñ¹Ø¿¨    
	QAction *restartGameAction;//ÖØÐÂ¿ªÊ¼    
	QAction *endGameAction;//½áÊøÓÎÏ·    
	QAction *openMusicAction;//´ò¿ªÒôÀÖ    
	QAction *closeMusicAction;//¹Ø±ÕÒôÀÖ    
	QAction *aboutAction;//¹ØÓÚÎÒÃÇ    
	
	//******************Êý¾ÝÉè¼Æ*************************    
	//int map[LEVELNUM][MAPH][MAPV];    
	//int man[LEVELNUM][2];    
	//int box[LEVELNUM];  
	int map[5][MAPH][MAPV];
	int man[5][2];
	int box[5];
	int boxNum;    
	int chooseNum;    
	QSound *bells;    
	QTimer *timer;    
	
	//******************½çÃæ²¼¾Ö****************************    
	QWidget *widget;   
	 mapPaint *mainmap;   
	  QLabel *levelLabel;    
	  QLabel *stepLabel;    
	  QLCDNumber *levelLCD;    
	  QLCDNumber *stepLCD;    
	  QPushButton *restartButton;
	  QPushButton *beginButton;
	  QPushButton *upButton;
	  QPushButton *downButton;
	  QPushButton *leftButton;
	  QPushButton *rightButton;
	  
	void createMap();
	void createMenu();    
	void createAction();
	  //*************ÓÎÏ·¿ØÖÆ**********************    
	  
	  void keyPressEvent(QKeyEvent *e);    
	  void keyUp();    
	  void keyLeft();    
	  void keyRight();    
	  void keyDown();   
	  void boxNumCheck();    
	  void startGame(int x);
public slots:
	//******************²Ëµ¥À¸¡ª¡ª²Û**********************    
		void beginGameSlot();
		void keyDownSlot();
		void keyUpSlot();
		void keyLeftSlot();
		void keyRightSlot();    
		void chooseGameSlot();    
		void restartGameSlot();    
		void endGameSlot();    
		void openMusicSlot();    
		void closeMusicSlot();    
		void aboutSlot();    
		void levelLCDShow();//¹Ø¿¨ÏÔÊ¾    
		void stepLCDShow();//²½ÊýÏÔÊ¾    
		void soundSlot();
};

#endif  // MAINWINDOW_H