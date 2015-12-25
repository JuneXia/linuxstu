#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

#define MAXLINE 64 
#define SERV_PORT 8000 

int main(int argc, char*argv[]) 
{ 
	if(argc != 2) {
		printf("you should execute as : ./client message\n"); 
		return -1;
	}
	char *sendto_server_str = argv[1]; 

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("sockfd = %d\n", sockfd);
	if (sockfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	//inet_pton(AF_INET, "192.168.1.119", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	printf("we will connect\n");
	int rc = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (rc == -1)
	{
		perror("connect");
		close(sockfd);
		return -1;
	}

	printf("we will write\n");
	int n = write(sockfd, sendto_server_str, strlen(sendto_server_str));
	printf("n = %d, sendto_server_str = |%s|\n", n, sendto_server_str);

	printf("we will read\n");
	char buf[MAXLINE] = {0}; 
	n = read(sockfd, buf, MAXLINE);
	printf("n = %d, buf = |%s|\n", n, buf);

	printf("we will close\n");
	close(sockfd);
	return 0;
}
