#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <errno.h>

#define MAXLINE 64 
#define SERV_PORT 8000 

ssize_t mysend(int sockfd, const void *buf, size_t len, int flags)
{
        size_t pos = 0; // position
        int rc;
        const char *ptr = NULL;
        size_t size;
        while(pos < len)
        {
                ptr = buf + pos;
                size = len - pos;

                int rc = send(sockfd, ptr, size, flags);
		printf("send rc = %d\n", rc);
                if (rc == -1)
                {
			switch (errno)
			{
			case 0:
				break;
			case 1:
				printf("aa");
			
			}
			//return errno;
		}
                else
                {
                        pos += rc;
                }
        }
	return pos;
}

char *makestr(size_t size)
{
	int i;
	char *buf = malloc(size*8);
	for (i = 0; i < size; i++)
	{
		char str[64] = {0};
		sprintf(str, "%d  ", i);
		strcat(buf, str);
	}
	return buf;
}

int main(int argc, char*argv[]) 
{ 
	if(argc != 2) {
		printf("you should execute as : ./client message\n"); 
		return -1;
	}
	char *sendto_server_str = argv[1]; 

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	//inet_pton(AF_INET, "192.168.1.119", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	int rc = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (rc == -1)
	{
		perror("connect");
		close(sockfd);
		return -1;
	}

	size_t LEN = 1024;
	char *buf = makestr(LEN);
	//write(sockfd, sendto_server_str, strlen(sendto_server_str));
	mysend(sockfd, buf, strlen(buf), MSG_DONTWAIT | MSG_NOSIGNAL);

	memset(buf, 0, LEN);
	int n = read(sockfd, buf, LEN*8);
	printf("n = %d, buf = |%s|\n", n, buf);

	close(sockfd);
	free(buf);
	return 0;
}
