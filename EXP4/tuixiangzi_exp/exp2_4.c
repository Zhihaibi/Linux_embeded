#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define MAX_SIZE 5000

int set_opt(int,int,int,char,int);
int fd_adc=0;

// 获取ADC值
int getADC(){
    char buffer[20];
    memset(buffer,0, 20);
    int len=read(fd_adc,buffer,12);
    if(len == 0)
    {
        printf("ADC read error \n");
        return -1;
    }
    int value = atoi(buffer);
    value = value*10000/4096;
    return value;
}


void main()
{
	char *buzzer = "/dev/buzzer_ctl";
	int fd_uart,fd_file，fd_bz;

	//设备地址
	char *IOtest = "./test.txt";
	char *buzzer = "/dev/buzzer_ctl";
    char *uart3="/dev/ttySAC3";
	char *uart_out = "\nhello uart3\r\n";

	//打开设备
	if((fd_adc = open("/dev/adc", O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		printf("open ADC error\n");
		return;
	}
	if((fd_bz = open(buzzer, O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		printf("open buzzer error\n");
		return;
	}
	if((fd_uart = open(uart3,O_RDWR | O_NOCTTY | O_NDELAY,0777))<0){
        printf("open %s is failed",uart3);
        return;
	}

    // 初始化串口3，波特率115200,8位数据位，无校验，1位停止位
    set_opt(fd_uart, 115200, 8, 'N', 1);

    // 将uart_out字符串通过串口发送出去
    write(fd_uart, uart_out, strlen(uart_out));

    // 打开文件IO实验写入的文件
    if((fd_file = open(IOtest,O_RDWR | O_TRUNC ,0777))<0){
        printf("open %s failed!\n",IOtest);
        close(fd_uart);
        return;
    }

    else{
        printf("opened file:%s\n", IOtest);
        char str[100]="08117106\r\n08117105\r\n";
        write(fd_file,str,strlen(str));
    }

	//关闭文件
	close(fd_file);

	// 再打开文件
	if((fd_file = open(IOtest,O_RDWR|O_TRUNC,0777))<0){
		printf("open %s failed!\n",IOtest);
	}

    int count = 0;      // 记录写文件次数
    char buffer[1000];
    unsigned char buffer_int[10] = {0};

    while(1){

       int i;
		for(i= 0; i< 10 ;i++)
			buffer_int[i] = 0;
				
		int value=getADC();
		value = value / 100;
		char *alert;
		if(value>90){
			alert="HI";
			buffer_int[2] = 72;
			buffer_int[3] = 73;
			ioctl(fd_bz,1);
			sleep(1);	
		}
		else if(value <10)
		{
			alert="LO";
			buffer_int[2] = 76;
			buffer_int[3] = 79;
			ioctl(fd_bz,1);
			sleep(1);	
		}
		else 
		{
			alert="OK";
			buffer_int[2] = 79;
			buffer_int[3] = 75;
			ioctl(fd_bz,0);	
		}
			
		buffer_int[0] = 0;
		buffer_int[1] = 1;
		buffer_int[2] = value;
		sprintf(buffer,"%d %d %d\r\n",0,1, value);
		write(fd_file, buffer, strlen(buffer));    // 写到文件
		write(fd_uart, buffer_int, 3);             // 写到串口
		count++;
		int R = 0;

		if(count%5 == 0)
		{
		    printf("save file and exit\r\n");
		    lseek(fd_file,0,SEEK_SET);  
		    read(fd_file,buffer,1000);
            for(i = 0;i<=4; i++)
            {
                R = (buffer[4 + 8*i] - '0') *1000 + (buffer[5 + 8*i]-'0')*100 ;
                if(R > 9000)
					alert="HI";
				else if(R < 1000)
					alert="LO";
				else 
					alert="OK";

                printf("\nRessitance: %d, Alert:%s\r\n", R, alert);
             }

            //关闭文件
		    close(fd_file);
		    close(fd_uart);
		    close(fd_adc);
		    return;
		}
		sleep(2);  // 延时2s
    }
}

/************************************
* 函数：串口初始化函数
* 参数：
	fd:打开串口返回的句柄
	nSpeed：波特率
	nBits：数据位
	nEvent：奇偶校验 "o"奇校验 "E"偶校验 "N" 无校验
	nStop：停止位
*返回值： return 0
***********************************/
int set_opt(int fd_uart,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd_uart,&oldtio)  !=  0) {
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E':
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 ){
		newtio.c_cflag |=  CSTOPB;
		newtio.c_cc[VTIME]  = 0;
		newtio.c_cc[VMIN] = 0;
		tcflush(fd_uart,TCIFLUSH);
	}
	if((tcsetattr(fd_uart,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}

	//	printf("set done!\n\r");
	return 0;
}


