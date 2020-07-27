#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <QPainter>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QLineEdit>
#include <QTimer>
#include <pthread.h>
#include <QProcess>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <fstream>
#include <QDateTime>
//#include <QImage>
#include "qt1.h"
#include "dlinklist.c"		//undefined reference

static int i=0;
static int j = 0;
int frame_time = 100;
static QString filepath1 = "/photo_exp/";
bool iscamera = false;
//DLIST* Qt1:: p=NULL;
DLIST *p;
DLIST *q;
DLIST head;
void insert_dlinklist(DLIST *d,char *s);

//=====just for you to learn how to use comboBox=======
void Qt1::InitBox()
{
    comboBox->clear();
    QStringList strList;
    strList<<"0.1"<<"0.2"<<"0.3"<<"0.4"<<"0.5";
    comboBox->addItems(strList);
}


void Qt1::fun_refresh_label()
{
	//comboBox->currentText();
}

//=====just for you to learn how to use comboBox=======

Qt1::Qt1(QWidget *parent):QDialog(parent)
{
  	setupUi(this);
//  rb_manual->setChecked(true);
    isCapOpen = false;
    isToSave = false;
    m_image = NULL;
	rb_manual->setDisabled(false);
	rb_auto->setDisabled(false);
	pb_prev->setDisabled(true);
	pb_next->setDisabled(true);
	pb_sure->setDisabled(false);
    pb_del->setDisabled(true);
	pb_opencamera->setDisabled(false);
	pb_save->setDisabled(true);

//=====just for you to learn how to use comboBox=======
	//InitBox();
	//connect(&t3, SIGNAL(timeout()), this, SLOT(fun_refresh_label()));
	//t3.start(100);
//=====just for you to learn how to use comboBox=======
	connect(rb_auto,SIGNAL(clicked()),this,SLOT(fun_cntl())); 
	connect(rb_manual,SIGNAL(clicked()),this,SLOT(fun_cntl())); 
	connect(pb_prev,SIGNAL(clicked()),this,SLOT(fun_prev())); 
	connect(pb_next,SIGNAL(clicked()),this,SLOT(fun_pic())); 
	connect(pb_del,SIGNAL(clicked()),this,SLOT(fun_delete())); 	
	connect(pb_open,SIGNAL(clicked()),this,SLOT(fun_open())); 	
	connect(pb_opencamera, SIGNAL(clicked()), this, SLOT(fun_cap_open()));
	connect(pb_sure, SIGNAL(clicked()), this, SLOT(Time_change()));
	connect(pb_save, SIGNAL(clicked()), this, SLOT(fun_take_photo()));
  	connect(&t1,SIGNAL(timeout()),this,SLOT(fun_time()));
 	connect(&t2,SIGNAL(timeout()),this,SLOT(fun_pic())); 
	connect(&t4, SIGNAL(timeout()), this, SLOT(fun_refresh_pic()));
	connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(time_s()));
  	t1.start(1000);						//
	init_dlinklist(&head);
    width = 320;
    height = 240;
    myCamera = new Camera("/dev/video0", width, height, 0);
    frameBufRGB = new unsigned char[width * height * 3];
    frameBufYUV = new unsigned char[width * height * 2];
}



void Qt1::time_s()
{
	if (comboBox->currentIndex() == 0) frame_time = 100;
	else if (comboBox->currentIndex() == 1)  frame_time = 200;
	else if (comboBox->currentIndex() == 2)  frame_time = 300;
	else if (comboBox->currentIndex() == 3)  frame_time = 400;
	else  frame_time = 500;
}


void Qt1::Time_change()
{
	t4.start(frame_time);
	printf("frame_time:%d", frame_time);
}


void Qt1::fun_refresh_pic()
{
   if(!myCamera->GetBuffer(frameBufYUV))
   {
       std::cout<< "Get Camera Buf error!\n";
       return;
   }
   //TODO:process_image() function is now empty.
   myCamera->process_image(frameBufYUV, frameBufRGB);
   showCapPhoto();
}



void Qt1::fun_cap_open()
{
	if (!iscamera)
	{
        t4.start(frame_time);
		iscamera = true;
		myCamera->OpenDevice();
		pb_opencamera->setText("close camera");

		pb_save->setDisabled(false);
        output->setText("open camera");
        t2.stop();
	} 
	else
	{
		iscamera = false;
		t4.stop();
		fun_clean_pixmap();
		pb_save->setDisabled(true);
		pb_opencamera->setText("open camera");
		myCamera->CloseDevice();
        output->setText("close camera");

	}
}


void Qt1::fun_clean_pixmap()
{
    QPixmap p;
    lb_pic->setPixmap(p);
}


void Qt1::fun_take_photo()
{
    QDateTime d=QDateTime::currentDateTime();
    QString datastr=d.toString("yyyy-MM-dd-ddd\nhh:mm:ss");
    //TODO: When this button is clicked, we take a photo and save it.

    filepath1 += datastr;
	filepath1 += ".jpg";
	QByteArray a = filepath1.toUtf8();
	char *c = a.data();
	std::cout << c << "\n";
	m_image->save(filepath1, "JPG", -1);
	j++;
    filepath1 = "/photo_exp/";
    output->setText("saved img");
}


void Qt1::showCapPhoto()
{
    if(m_image != NULL)
        delete m_image;
    m_image = NULL;
    m_image = new QImage(frameBufRGB, width, height, QImage::Format_RGB888);
    lb_pic->setPixmap(QPixmap::fromImage(*m_image));
}


void Qt1::fun_time()
{
    QDateTime d=QDateTime::currentDateTime();

    lb_time->setText(d.toString("yyyy-MM-dd-ddd\nhh:mm:ss"));	//
}

void Qt1::fun_cntl()
{
	if(rb_manual->isChecked ())
	{
		t2.stop();
		pb_prev->setEnabled(true);	
		pb_next->setEnabled(true);	
	}
	else if(rb_auto->isChecked ())
	{
        t2.start(1000);
		pb_prev->setEnabled(false);	
		pb_next->setEnabled(false);	
	}
}

void Qt1::fun_pic()		
{
	i++;
	if(i==(len+1))
		i=1;

	p=p->next;
	display_pic();
}


void Qt1::fun_prev()	//fun_next()��fun_pic()һ��
{
	i--;
	if(i==0)i=len;
	p=p->prev;
	display_pic();
}

void Qt1::display_pic()
{
	QString buf(p->path);
	QPixmap p(buf);
	lb_pic->setPixmap(p);
	lb_pic->setScaledContents(1);
//	lb_num->setText(QString::number(i));
//	lb_sum->setText(QString::number(len));
    char obuf[50];
    sprintf(obuf, "curent / total: %d / %d", i, len);
    output->setText(obuf);

}


void Qt1::fun_delete()
{
	int ret;
        ret=QMessageBox::warning(this, tr("m_image browser"),
					   tr("Are you sure to delete it?"),
					   QMessageBox::Yes | QMessageBox::No,
					   QMessageBox::No);
	if(ret==QMessageBox::Yes)
	{
		remove(p->path);
		DLIST *r=(&head)->next;
		int n=1;
		while(r!=p)		//
		{
			n++;
			r=r->next;
		}
		p=p->next;
        del_dlinklist(&head,n);
		if(i==len)i--;
		len=legnth_dlinklist(&head);
		display_pic();
	}
//	dlinkilist_tofile(&head);
}


void Qt1::fun_open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "/",
                                                 tr("Images (*.png *.xpm *.jpg)"));
	printf("open folder!\n");
	if(fileName!=NULL)
	{
        init_dlinklist(&head);
		char *str;
		char filename[100]={0};
        DIR *dp;
        struct dirent *dirp;
		int m=strlen(fileName.toAscii().data());
		str=(char*)malloc(m);
		strcpy(str,fileName.toAscii().data());
		strcpy(filename,str);

		QString buf(fileName.toAscii().data());
		QPixmap first(buf);
		lb_pic->setPixmap(first);
        lb_pic->setScaledContents(false);
		
		strip(filename);
		dp=opendir(filename);
		while(dirp=readdir(dp))
		{
			if(judge(dirp->d_name)==1)
			{
				strcat(filename,"/");
				strcat(filename,dirp->d_name);	//
				printf("%s\n",filename);
				insert_dlinklist(&head,filename);
				filename[strlen(filename)-strlen(dirp->d_name)-1]='\0';
			}	
		}
		q->next=(&head)->next;
		(&head)->next->prev=q;
		
		len=legnth_dlinklist(&head);
		int pos=1;
		DLIST *r=(&head)->next;
		while(strcmp(r->path,str)!=0)
		{
			r=r->next;
			pos++;
		}
		p=r;
		i=pos;
//		lb_num->setText(QString::number(i));
//		lb_sum->setText(QString::number(len));
        char obuf[50];
        sprintf(obuf, "curent / total: %d / %d", i, len);
        output->setText(obuf);
		rb_manual->setDisabled(false);
		rb_auto->setDisabled(false);
		pb_prev->setDisabled(false);
		pb_next->setDisabled(false);
		pb_del->setDisabled(false);
		rb_manual->setChecked(true);
//		display_pic();
	}
//	dlinkilist_tofile(&head);
}

void Qt1::strip(char *s)
{
	char *p=s;
	int n=0;
	while(*p)
	{
		if(*p=='/')
		{
			n++;
		}
		p++;
	}
	if(n==1)
	{
		s[1]='\0';
	}
	else
	{
		p--;
		while(*p)
		{
			if(*p=='/')
			{
				*p='\0';
				break;
			}
			p--;
		}
	}
}

int Qt1::judge(char * s)	
{
	int i,len=strlen(s);
	char *p=s;
	if(len<5)
	{
		return 0;
	}
	else 
	{
		while(*p)
		{
			p++;
		}
		for(i=0;i<4;i++)p--;
		if((strncmp(p,".jpg",4)==0)||(strncmp(p,".png",4)==0)||(strncmp(p,".xpm",4)==0))
		{
			return 1;
		}
		else 
			return 0;
	}
}

void insert_dlinklist(DLIST *d,char *s)	//������ĩβ����,֮���԰���������ᵽ�������Ϊ����ʹ��ȫ�ֱ���DLIST *q
{
	DLIST *r=d;
//	DLIST *q;
	q=(DLIST*)malloc(sizeof(DLIST));	//�����q�����Ǿֲ��ģ������޷��γ�˫��ѭ������
	memset(q,0,sizeof(q));
	strcpy(q->path,s);

	if(r->next==NULL)
	{
		r->next=q;
		q->next=NULL;
	}
	else
	{
		while(r->next!=NULL)
		{
			r=r->next;
		}
		r->next=q;
		q->prev=r;
		q->next=NULL;
	}
	printf("insert success\n");
}


Qt1::~Qt1()
{
    delete[] frameBufRGB;
    delete[] frameBufYUV;
    delete m_image;
}

//int Qt1::OnBtnOK()
//{
//	int index = cmbR->currentIndex();
//	output->setText("connected");
//  index=(index+1)*100;
//	printf("%d\n",index);
//	return 0;
//}
