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

	write(sockfd, sendto_server_str, strlen(sendto_server_str));

	char buf[MAXLINE] = {0}; 
	int n = read(sockfd, buf, MAXLINE);
	printf("n = %d, buf = |%s|\n", n, buf);

	close(sockfd);
	return 0;
}
