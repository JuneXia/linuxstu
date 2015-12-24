#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <errno.h>

#define MAXLINE 64 
#define SERV_PORT 8000 

int main() 
{ 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	int rc = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (rc == -1)
	{
		perror("connect");
		close(sockfd);
		return -1;
	}

	usleep(100);
	char buf[MAXLINE] = {"0123456789abcdefghijklmnopqrstuvwsyz"};
	//char buf[MAXLINE] = {"0123456789"};
	//send(sockfd, buf, strlen(buf), MSG_DONTWAIT | MSG_NOSIGNAL);
	send(sockfd, buf, strlen(buf), 0);
	sleep(3);

	close(sockfd);
	return 0;
}
