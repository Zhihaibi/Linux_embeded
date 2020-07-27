#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAXLINE 4096


int main(){
    int   sockfd, len;
    char  buffer[MAXLINE];
    char  buffer_R[] = "8500";
    struct sockaddr_in  servaddr;
    FILE *fq;
    char str[] = "192.168.1.110";

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, str, &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",str);
        return 0;
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    if( ( fq = fopen("./ui/background.jpg","rb") ) == NULL ){
        printf("File open.\n");
        close(sockfd);
        exit(1);
    }

    bzero(buffer,sizeof(buffer));
    
    send(sockfd, buffer_R, strlen(buffer_R), 0); // 阻值

    // while(!feof(fq)){
    //     len = fread(buffer, 1, sizeof(buffer), fq);
    //     if(len != write(sockfd, buffer, len)){
    //         printf("write.\n");
    //         break;
    //     }

    // }

    close(sockfd);
    fclose(fq);
    return 0;
}
