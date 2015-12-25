/*select_socket.c*/ 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/un.h> 
#include <sys/time.h> 
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <netinet/in.h> 
#define SERVPORT 8000
#define BACKLOG 10 
#define MAX_CONNECTED_NO 10 
#define MAXDATASIZE 100 

int main() 
{ 
	struct sockaddr_in server_sockaddr,client_sockaddr; 
	int sin_size,recvbytes; 
	fd_set readfd; 
	fd_set writefd; 
	int sockfd,client_fd; 
	char buf[MAXDATASIZE]; 

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket"); 
		exit(1); 
	} 
	printf("socket success!,sockfd=%d\n",sockfd); 

	server_sockaddr.sin_family=AF_INET; 
	server_sockaddr.sin_port=htons(SERVPORT); 
	server_sockaddr.sin_addr.s_addr=INADDR_ANY; 
	bzero(&(server_sockaddr.sin_zero),8); 

	if(bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind"); 
		exit(1); 
	} 
	printf("bind success!\n"); 

	if(listen(sockfd,BACKLOG) == -1)
	{
		perror("listen"); 
		exit(1); 
	} 
	printf("listening....\n"); 
	FD_ZERO(&readfd);

	/*将调用socket 函数的描述符作为文件描述符*/ 
	while(1)
	{
		FD_SET(sockfd,&readfd);
		printf("we will select\n");
		sin_size=sizeof(struct sockaddr_in); 
		/*调用select 函数*/ 
		struct timeval time;
		time.tv_sec = 5;
		time.tv_usec = 0;
		//if(select(MAX_CONNECTED_NO,&readfd,NULL,NULL,(struct timeval *)0)>0)
		if(select(MAX_CONNECTED_NO,&readfd,NULL,NULL,&time)>0)
		{
			printf("we will FD_ISSET\n");
			if(FD_ISSET(sockfd,&readfd)>0)
			{
				printf("we will accept\n");
				if((client_fd=accept(sockfd,(struct sockaddr *)&client_sockaddr,&sin_size)) == -1)
				{
					perror("accept"); 
					exit(1); 
				} 

				printf("we will recv\n");
				if((recvbytes=recv(client_fd,buf,MAXDATASIZE,0)) == -1)
				{
					perror("recv"); 
					exit(1); 
				}

/*
				printf("we will read\n");
				if(read(client_fd,buf,MAXDATASIZE)<0)
				{
					perror("read"); 
					exit(1); 
				} 
*/

				printf("received a connection :%s\n",buf); 

				send(client_fd, buf, recvbytes, MSG_DONTWAIT);
			}/*if*/ 
			printf("we will close(client_fd)\n");
			close(client_fd); 
		}/*select*/ 
		printf("select end\n");
		FD_CLR(sockfd, &readfd);
	}/*while*/ 
} 
