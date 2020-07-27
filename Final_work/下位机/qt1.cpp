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
#include "communicate.h"
#include "chart.h"



int pub_adc_peroid = 500;

extern chart* adc_curve_chart;
static int i=0;
static int j = 0;
int frame_time = 100;
int flag_same = 0;
int adc_value = 0;
int pic_num = 0;
int flag_connect = 1;
static QString filepath1 = "/photo_exp/";
bool iscamera = false;
DLIST *p;
DLIST *q;
DLIST head;
void insert_dlinklist(DLIST *d,char *s);
unsigned char pre_pic[320 * 240 *2]; //±£´æÇ°Ò»Ö¡Í¼Æ¬
unsigned char now_pic[320 * 240 *2]; //±£´æµ±Ç°Ò»Ö¡Í¼Æ¬



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


Qt1::Qt1(QWidget *parent):QDialog(parent)
{
    setupUi(this);
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
    pb_communicate->setDisabled(false);
    pb_chart->setDisabled(false);


    connect(rb_auto,SIGNAL(clicked()),this,SLOT(fun_cntl()));
    connect(rb_manual,SIGNAL(clicked()),this,SLOT(fun_cntl()));
    connect(pb_prev,SIGNAL(clicked()),this,SLOT(fun_prev()));
    connect(pb_next,SIGNAL(clicked()),this,SLOT(fun_pic()));
    connect(pb_del,SIGNAL(clicked()),this,SLOT(fun_delete()));
    connect(pb_open,SIGNAL(clicked()),this,SLOT(fun_open()));
    connect(pb_opencamera, SIGNAL(clicked()), this, SLOT(fun_cap_open()));
    connect(pb_sure, SIGNAL(clicked()), this, SLOT(Time_change()));
    connect(pb_communicate, SIGNAL(clicked()), this, SLOT(fun_communicate()));
    connect(pb_chart, SIGNAL(clicked()), this, SLOT(fun_chart()));
    connect(pb_save, SIGNAL(clicked()), this, SLOT(fun_take_photo()));
    connect(&t1,SIGNAL(timeout()),this,SLOT(fun_time()));
    connect(&t2,SIGNAL(timeout()),this,SLOT(fun_pic()));
    connect(&t4, SIGNAL(timeout()), this, SLOT(fun_refresh_pic()));
    connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(time_s()));
    connect(&img_timer, SIGNAL(timeout()), this, SLOT(fun_send_img()));

    //connect(&adc_timer, SIGNAL(timeout()), this, SLOT(fun_send_R()));
    connect(&adc_timer, SIGNAL(timeout()), this, SLOT(show_adc()));


    init_ADC_LED_buzzer();
    adc_timer.start(500);

    img_timer.start(500);

    t1.start(1000);

    init_dlinklist(&head);
    width = 320;
    height = 240;
    myCamera = new Camera("/dev/video0", width, height, 0);

    frameBufRGB = new unsigned char[width * height * 3];
    frameBufYUV = new unsigned char[width * height * 2];
}


void Is_Same()
{
    int i = 0,sum = 0 ,err = 0;
    for(i=0; i<(320*240*2);i++)
    {
        err = pre_pic[i] - now_pic[i];
        sum += abs(err);
    }
    printf("sum:%d\n",sum);

    if(sum > 30)
        flag_same = 0;
    else
        flag_same = 1;
}



//void Qt1::fun_send_R()
//{
//    adc_timer.start(pub_adc_peroid);
//    Send_R(adc_value);
//}




void Qt1::fun_communicate()
{
    flag_connect++;

}

char str2[10] = {0};
char *int_to_string2(int num)
{

        int i=0,j=0;
        char temp[10];

        while(num)
        {
        temp[i++]=num%10+'0';  //½«Êý×Ö¼Ó×Ö·û0¾Í±ä³ÉÏàÓ¦×Ö·û
        num/=10;               //´ËÊ±µÄ×Ö·û´®ÎªÄæÐò
        }
    temp[i]='\0';
        i=i-1;
        while(i>=0)
    str2[j++]=temp[i--];   //½«ÄæÐòµÄ×Ö·û´®×ªÎªÕýÐò
        str2[j]='\0';               //×Ö·û´®½áÊø±êÖ¾
        return str2;
}


void Qt1::fun_send_img()
{

    if(flag_connect % 2 == 0)
    {
        if(flag_same == 0)
        {
            pic_num++;
            QDateTime d=QDateTime::currentDateTime();
            QString datastr = d.toString("yyyy-MM-dd-ddd\nhh:mm:ss");

            filepath1 += datastr;
            filepath1 += ".jpg";

            QByteArray a = filepath1.toUtf8();
            char *c = a.data();
            std::cout << c << "\n";
            m_image->save(filepath1, "JPG", -1);
            j++;
            output->setText("saved img");
            pb_communicate->setText("disconnect");

            Send_img(filepath1);

            filepath1 = "/photo_exp/";

            char client_message[]= "I get photo";
            strcat(client_message,int_to_string2(pic_num));
            lb_msg->setText(client_message);
        }

    }

    else
    {
       pb_communicate->setText("connect");
    }
}


void Qt1::fun_chart()
{
    //emit sig_update_curve();
    adc_curve_chart->activateWindow();
    adc_curve_chart->setFocus();
    adc_curve_chart->show();
}



void Qt1::show_adc()
{
	adc_value = read_ADC();
	const char *alert = adc_value > 9000 ? "Too high!" : adc_value < 1000 ? "Too low!" : "None";
	char buf[30];
	int len = sprintf(buf, "%d Ohm, %s", adc_value, alert);
	lb_adc->setText(buf);

        //adc_timer.start(pub_adc_peroid);
        Send_R(adc_value);
}


void Qt1::time_s()
{
        if (comboBox->currentIndex() == 0) pub_adc_peroid = 100;
        else if (comboBox->currentIndex() == 1)  pub_adc_peroid = 200;
        else if (comboBox->currentIndex() == 2)  pub_adc_peroid = 300;
        else if (comboBox->currentIndex() == 3)  pub_adc_peroid = 400;
        else  pub_adc_peroid = 500;
}


void Qt1::Time_change()
{
        adc_timer.start(pub_adc_peroid);
	printf("frame_time:%d", frame_time);
}



void Qt1::fun_refresh_pic()
{
   memcpy(pre_pic,frameBufYUV,sizeof(frameBufYUV));

   if(!myCamera->GetBuffer(frameBufYUV))
   {
       std::cout<< "Get Camera Buf error!\n";
       return;
   }
   //TODO:process_image() function is now empty.
   memcpy(now_pic,frameBufYUV,sizeof(frameBufYUV));

   Is_Same();


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
    lb_time->setText(d.toString("yyyy-MM-dd-ddd\nhh:mm:ss"));	
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
	if(i==(len+1))i=1;

	p=p->next;
	display_pic();
}


void Qt1::fun_prev()	//fun_next()ï¿½ï¿½fun_pic()Ò»ï¿½ï¿½
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
		while(r!=p)		//ï¿½Òµï¿½ï¿½ï¿½Ç° pï¿½ï¿½Î»ï¿½ï¿½
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
				strcat(filename,dirp->d_name);	//ï¿½Ä¼ï¿½ï¿½ï¿½ï¿½Úµï¿½Ä¿Â¼+ï¿½Ä¼ï¿½ï¿½ï¿½=ï¿½ï¿½ï¿½ï¿½Â·ï¿½ï¿½
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

void insert_dlinklist(DLIST *d,char *s)	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä©Î²ï¿½ï¿½ï¿½ï¿½,Ö®ï¿½ï¿½ï¿½Ô°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½áµ½ï¿½ï¿½ï¿½ï£¬ï¿½ï¿½ï¿½ï¿½Îªï¿½ï¿½ï¿½ï¿½Ê¹ï¿½ï¿½È«ï¿½Ö±ï¿½ï¿½ï¿½DLIST *q
{
	DLIST *r=d;
//	DLIST *q;
	q=(DLIST*)malloc(sizeof(DLIST));	//ï¿½ï¿½ï¿½ï¿½ï¿½qï¿½ï¿½ï¿½ï¿½ï¿½Ç¾Ö²ï¿½ï¿½Ä£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Þ·ï¿½ï¿½Î³ï¿½Ë«ï¿½ï¿½Ñ­ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
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
