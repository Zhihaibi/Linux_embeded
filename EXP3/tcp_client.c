#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
	int clientSocket;  //客户端只需要一个套接字文件描述符，用于和服务器通信
	int recbyte;
	int sin_size;
	char buffer[1024] = { 0 };

	struct sockaddr_in server_add, client_add; //描述服务器的socket  套接字的数据结构
	unsigned short portnum = 2333; //端口号

	printf("Hello,welcome to client!\r\n");

	if(argc != 2)
	{
			printf("usage: echo ip\n");
			return -1;
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0); //建立一个socket连接

	if(-1 == clientSocket)
	{
			printf("socket fail ! \r\n");
			return -1;
	}
	printf("socket ok !\r\n");
	bzero(&server_add,sizeof(struct sockaddr_in));  //置零
	server_add.sin_family=AF_INET;  //地址族
	server_add.sin_addr.s_addr = inet_addr(argv[1]);  //地址
	server_add.sin_port=htons(portnum); //端口号
	
    printf("IP is %s\n", inet_ntoa(server_add.sin_addr));
    printf("Port is %d\n", htons(server_add.sin_port));

	//面向连接的client程序使用connect函数来配置socket，并与远端服务器建立TCP连接
	if(-1 == connect(clientSocket,(struct sockaddr *)(&server_add), sizeof(struct sockaddr)))
	{
			printf("connect fail !\r\n");
			return -1;
	}
	printf("connect ok !\r\n");


	// 网络连接完成，登陆
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

    char namebuf[100];
	char passbuf[100];

	scanf("%s",namebuf);  // 用户名
	scanf("%s",passbuf);  // 密码
	while(strlen(namebuf)>20 || strlen(passbuf) > 20)
	{
		printf("User name or the password is too long! Rewrite again!");
		scanf("%s",namebuf);  // 用户名
		scanf("%s",passbuf);  // 密码
	}

	strcat(namebuf,passbuf);
	printf("Send: %s\n",namebuf);
	send(clientSocket, namebuf, strlen(namebuf), 0); // 发送用户名密码

	// 等待接收信息
	recvbuf[0] = '\0';
	iDataNum = recv(clientSocket, recvbuf, 200, 0);
	while(iDataNum<0)
	{
		recvbuf[0] = '\0';
		int iDataNum = recv(clientSocket, recvbuf, 200, 0);
		perror("recv null");
	}
	printf("Receive:");
    recvbuf[iDataNum] = '\0';
	printf("%s\n", recvbuf);
	

	//登陆成功后互发信息
	while(1)
	{
        time_t timep;
        time (&timep);
        char mybuf[100];
		char sendbuf[100];


		scanf("%s",mybuf);
        sprintf(sendbuf,"%s08117106 BiZhihai\n08117105 OuYaming\n",asctime(gmtime(&timep)));
        strcat(sendbuf, mybuf);
        
		char recvbuf[1024];
		printf("Send: \n");
		send(clientSocket, sendbuf, strlen(sendbuf), 0);

		printf("Receive:");
		recvbuf[0] = '\0';
		int iDataNum = recv(clientSocket, recvbuf, 200, 0);
		recvbuf[iDataNum] = '\0';
		printf("%s\n", recvbuf);
		if(strcmp(recvbuf, "quit")==0){
            break;
		}
	}

	close(clientSocket);
	return 0;
}

