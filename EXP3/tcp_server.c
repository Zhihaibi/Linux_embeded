#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


void* thread(void* arg);
int main()
{
	//serverSocket 调用socket函数返回的文件描述符
	int serverSocket, nfp, num = 0;
	int flag = 0;

	//声明两个套接字sockaddr_in结构体变量，分别表示客户端和服务器  描述服务器的socket
	struct sockaddr_in server_add,client_add;
	int sin_size;
	unsigned short portnum=2333;

	char recvbuf[200] = {0};
	char sendbuf[200];

	printf("Hello,welcome to my server !\r\n");

	//socket函数，失败返回-1
	//int socket(int domain, int type, int protocol);
	//第一个参数表示使用的地址类型，一般都是ipv4，AF_INET
	//第二个参数表示套接字类型：tcp：面向连接的稳定数据传输SOCK_STREAM
	//第三个参数设置为0
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == serverSocket)
	{
			printf("socket fail ! \r\n");
			return -1;
	}
	printf("socket ok !\r\n");

	//初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
	bzero(&server_add,sizeof(struct sockaddr_in));
	server_add.sin_family=AF_INET;
	server_add.sin_addr.s_addr=htonl(INADDR_ANY);//ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
	server_add.sin_port=htons(portnum);
	

	//bind 将socket与本机的一个端口绑定，随后就可以在该端口上监听服务请求
	if(-1 == bind(serverSocket,(struct sockaddr *)(&server_add), sizeof(struct sockaddr)))
	{
			printf("bind fail !\r\n");
			return -1;
	}

	printf("bind ok !\r\n");
	printf("serverSocket %d\r\n",serverSocket);

	//设置服务器上的socket为监听状态
	if(-1 == listen(serverSocket,5))
	{
			printf("listen fail !\r\n");
			return -1;
	}

	printf("listen ok\r\n");


	sin_size = sizeof(struct sockaddr_in);
	nfp = accept(serverSocket, (struct sockaddr *)(&client_add), &sin_size);
	if(-1 == nfp)
	{
		printf("accept fail !\r\n");
		return -1;
	}

	//打印 IP Port
	//ntohl()---- 网络顺序转换成主机顺序
	printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n",
		ntohl(client_add.sin_addr.s_addr), ntohs(client_add.sin_port));


	// 开始发送登陆信息
	memset(recvbuf, 0, 100);
	sprintf(recvbuf, "Please input user name and password", num++);
	send(nfp, recvbuf, strlen(recvbuf), 0);
	usleep(500000);
	
	recvbuf[0] = '\0';
	int iDataNum = recv(nfp, recvbuf, 1024, 0);

	// 阻塞登陆
	while(iDataNum < 0)
	{
		recvbuf[0] = '\0';
		int iDataNum = recv(nfp, recvbuf, 1024, 0);
		perror("recv null");
	}

	printf("Received:");
	recvbuf[iDataNum] = '\0';
	printf("%s\n", recvbuf);


	if (strcmp(recvbuf, "abcdef") == 0)
	{
		sprintf(recvbuf, "login successfully!) \r\n", num++);
		send(nfp, recvbuf, strlen(recvbuf), 0);
		usleep(500000);
		flag = 1;
	}
	else
	{
		sprintf(recvbuf, "login fail,disconnect!) \r\n", num++);
		send(nfp, recvbuf, strlen(recvbuf), 0);
		usleep(500000);
	}
	

	while(flag == 1)
	{
		memset(recvbuf, 0, 100);
		sprintf(recvbuf, "hello,08117105 OuYaming 08117106 BiZhihai(%d) \r\n", num++);
		send(nfp, recvbuf, strlen(recvbuf), 0);
		usleep(500000);

		//printf("Received:\n");
		recvbuf[0] = '\0';
		iDataNum = recv(nfp, recvbuf, 1024, 0);
		if (iDataNum < 0)
		{
			perror("recv null");
			continue;
		}
		recvbuf[iDataNum] = '\0';
		printf("%s\n", recvbuf);

		if (strcmp(recvbuf, "quit") == 0)
			break;

		strcpy(sendbuf, "I heard!");
		send(nfp, sendbuf, strlen(sendbuf), 0);
	}

	close(nfp);
	close(serverSocket);
	return 0;
}




