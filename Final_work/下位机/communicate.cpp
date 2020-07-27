#include "communicate.h"

#define MAXLINE 4096

int clientSocket;
int flag_i = 0;

void connect()
{
     //客户端只需要一个套接字文件描述符，用于和服务器通信
    int recbyte;
    int sin_size;
    char buffer[1024] = { 0 };
    char str[] = "192.168.1.110";

    struct sockaddr_in server_add, client_add; //描述服务器的socket  套接字的数据结构
    unsigned short portnum = 8765; //端口号

    printf("Hello,welcome to client!\r\n");

    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //建立一个socket连接

    if(-1 == clientSocket)
    {
                    printf("socket fail ! \r\n");
                    return;
    }

    printf("socket ok !\r\n");
    bzero(&server_add,sizeof(struct sockaddr_in));  //置零
    server_add.sin_family=AF_INET;  //地址族
    server_add.sin_addr.s_addr = inet_addr(str);  //地址
    server_add.sin_port=htons(portnum); //端口号

    printf("IP is %s\n", inet_ntoa(server_add.sin_addr));
    printf("Port is %d\n", htons(server_add.sin_port));

    //面向连接的client程序使用connect函数来配置socket，并与远端服务器建立TCP连接
    if(-1 == connect(clientSocket,(struct sockaddr *)(&server_add), sizeof(struct sockaddr)))
    {
                    printf("connect fail !\r\n");
                    return;
    }
    printf("connect ok !\r\n");

    char sendbuf[100];
    sprintf(sendbuf,"%sI miss you!");
    send(clientSocket, sendbuf, strlen(sendbuf), 0);
    flag_i = 1;

}


void receive_msg()
{
    // 网络连接完成，接收上位机信息
    char recvbuf[1024];
    recvbuf[0] = '\0';
    int iDataNum = recv(clientSocket, recvbuf, 200, 0);
    while(iDataNum<0)
    {
            recvbuf[0] = '\0';
            int iDataNum = recv(clientSocket, recvbuf, 200, 0);
            perror("recv null");
    }
    printf("Receive:");
    recvbuf[iDataNum] = '\0';
    printf("%s\n", recvbuf);

    close(clientSocket);

    return;
}






void Send_img(QString filepath)
{
        connect();  //8765

	int   sockfd, len;
	char  buffer[MAXLINE];
	struct sockaddr_in  servaddr;
	FILE *fq;
	char str[] = "192.168.1.110";

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
                return;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	if (inet_pton(AF_INET, str, &servaddr.sin_addr) <= 0) {
		printf("inet_pton error for %s\n", str);
                return;
	}

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
                return;
	}

        char* ch;
        QByteArray ba = filepath.toLatin1(); // must
        ch=ba.data();

         qDebug()<<filepath<<"\n";
         qDebug()<<ch;

        if ((fq = fopen(ch, "rb")) == NULL) {
		printf("File open.\n");
		close(sockfd);
		exit(1);
	}

	bzero(buffer, sizeof(buffer));
	while (!feof(fq)) {
		len = fread(buffer, 1, sizeof(buffer), fq);
		if (len != write(sockfd, buffer, len)) {
			printf("write.\n");
			break;
		}
	}

	close(sockfd);
	fclose(fq);

        //接收上位机信息
        receive_msg();


        return;
}



char str[10] = {0};
char *int_to_string(int num)
{

        int i=0,j=0;
        char temp[10];

        while(num)
        {
        temp[i++]=num%10+'0';  //将数字加字符0就变成相应字符
        num/=10;               //此时的字符串为逆序
        }
    temp[i]='\0';
        i=i-1;
        while(i>=0)
    str[j++]=temp[i--];   //将逆序的字符串转为正序
        str[j]='\0';               //字符串结束标志
        return str;
}



void Send_R(int AD_value)
{
    int clientSocket;  //客户端只需要一个套接字文件描述符，用于和服务器通信
    int recbyte;
    int sin_size;
    char buffer[1024] = { 0 };
    char str[] = "192.168.1.110";

    struct sockaddr_in server_add, client_add; //描述服务器的socket  套接字的数据结构
    unsigned short portnum = 2444; //端口号

    //printf("Hello,welcome to client!\r\n");
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //建立一个socket连接
    if(-1 == clientSocket)
    {
                    printf("socket fail ! \r\n");
                    return ;
    }
    //printf("socket ok !\r\n");
    bzero(&server_add,sizeof(struct sockaddr_in));  //置零
    server_add.sin_family=AF_INET;  //地址族
    server_add.sin_addr.s_addr = inet_addr(str);  //地址
    server_add.sin_port=htons(portnum); //端口号

    //面向连接的client程序使用connect函数来配置socket，并与远端服务器建立TCP连接
    if(-1 == connect(clientSocket,(struct sockaddr *)(&server_add), sizeof(struct sockaddr)))
    {
                    printf("connect fail !\r\n");
                    return ;
    }
    printf("connect ok !\r\n");
    char *passbuf;
    passbuf = int_to_string(AD_value);
    printf("Send: %s\n",passbuf);
    send(clientSocket, passbuf, strlen(passbuf), 0); // 发送用户名密码
    close(clientSocket);
    return;
}
