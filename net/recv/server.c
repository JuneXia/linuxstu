#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <errno.h>

#define MAXLINE 64 
#define SERV_PORT 8000 

ssize_t myrecv(int sockfd, char **buf, size_t *len, int flags)
{
	const int step = 1024;
	*buf = malloc(step);
	if (*buf == NULL)
	{
		printf("myrecv() call >>> malloc return NULL, we will return -1\n");
		return -2;
	}
	memset(*buf, 0, step);
	*len = 0;

	int rc = 0;
	while (1)
	{
                rc = recv(sockfd, *buf + *len, step, flags);
		printf("myrecv() call >>> rc = %d, *buf = %s\n", rc, *buf);
		if (rc == 0)
		{
			printf("myrecv() call >>> rc == 0, we return 0\n");
			return rc;
		}
		else if (rc < 0)
		{
			printf("myrecv() call >>> rc <= 0, errno == %d, we depending on the stituation to deal with\n", errno);
			if (errno == EAGAIN && *len == 0)
			{
				printf("myrecv() call >>> errno == EAGAIN and *len == 0, we will continue to invoke recv\n");
				usleep(100);
				continue;
			}
			else
			{
				printf("myrecv() call >>> errno != EAGAIN or *len != 0, we will return -1\n");
				return rc;
			}
		}
		else if (rc == step)
		{
			printf("myrecv() call >>> rc == step(%d), we will renew memory to recv\n", step);
			*len += rc;
			char *p = realloc(*buf, *len + step);
			if (p == NULL)
			{
				printf("myrecv() call >>> realloc return NULL, we will return -2\n");
				//if(*buf) free(*buf);
				return -2;
			}
			*buf = p;
			memset(*buf + *len, 0, step);
		}
		else if (rc < step)
		{
			printf("myrecv() call >>> rc <= step(%d), we will break out recv\n", step);
			*len += rc;
			break;
		}
        }
	printf("myrecv() call >>> we will return soon, *len = %ld, *buf = %s\n", *len, *buf);
	return *len;
}

int main(void) 
{ 
	int listenfd = socket(AF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in servaddr;
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	listen(listenfd, 20); 
	printf("Accepting connections...\n"); 

	while(1) 
	{
		struct sockaddr_in cliaddr; 
		socklen_t cliaddr_len = sizeof(cliaddr); 
		int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len); 
		printf("connected ...\n");

		char *buf = NULL;
		size_t len = 0;
		//int n = myrecv(connfd, &buf, &len, MSG_DONTWAIT);
		int n = myrecv(connfd, &buf, &len, MSG_WAITALL);
		printf("n = %d, len = %ld, buf = %s\n", n, len, buf);

		sleep(1);
		free(buf);
		close(connfd); 
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	} 
}
