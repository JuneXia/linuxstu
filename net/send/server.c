#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 

#define MAXLINE 64 
#define SERV_PORT 8000 

int main(void) 
{ 
	int listenfd = socket(AF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	printf("INADDR_ANY = %d\n", INADDR_ANY);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	printf("servaddr.sin_addr.s_addr = %08X\n", servaddr.sin_addr.s_addr);
	servaddr.sin_port = htons(SERV_PORT); 

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	listen(listenfd, 20); 
	printf("Accepting connections...\n"); 

	while(1) 
	{
		struct sockaddr_in cliaddr; 
		socklen_t cliaddr_len = sizeof(cliaddr); 
		int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len); 
		printf("cliaddr_len = %d\n", cliaddr_len);

		char client_ip_str[INET_ADDRSTRLEN] = {0};
		inet_ntop(AF_INET, &cliaddr.sin_addr, client_ip_str, sizeof(client_ip_str)), 
		printf("received from %s at PORT %d\n", client_ip_str, ntohs(cliaddr.sin_port)); 

		size_t LEN = 1024*1024;
		char *buf = malloc(LEN);
		int n = read(connfd, buf, LEN); 
		printf("read return %d\n", n);

		int i;
		for(i=0; i<n; i++)
			buf[i] = toupper(buf[i]); 
		write(connfd, buf, n); 
		free(buf);
		close(connfd); 
	} 
}


int main2(void) 
{ 
	int listenfd = socket(AF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	printf("INADDR_ANY = %d\n", INADDR_ANY);
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	//inet_pton(AF_INET, "192.168.1.119", &servaddr.sin_addr);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	printf("servaddr.sin_addr.s_addr = %08X\n", servaddr.sin_addr.s_addr);
	servaddr.sin_port = htons(SERV_PORT); 

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	listen(listenfd, 20); 
	printf("Accepting connections...\n"); 

	while(1) 
	{
		struct sockaddr_in cliaddr; 
		socklen_t cliaddr_len = sizeof(cliaddr); 
		int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len); 

		char buf[MAXLINE] = {0};
		int n = read(connfd, buf, MAXLINE); 

		char client_ip_str[INET_ADDRSTRLEN] = {0};
		inet_ntop(AF_INET, &cliaddr.sin_addr, client_ip_str, sizeof(client_ip_str)), 
		printf("received from %s at PORT %d\n", client_ip_str, ntohs(cliaddr.sin_port)); 

		int i;
		for(i=0; i<n; i++)
			buf[i] = toupper(buf[i]); 
		write(connfd, buf, n); 
		close(connfd); 
	} 
}



int main3(void) 
{ 
	int listenfd = socket(AF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	int rc = inet_pton(AF_INET, "192.168.1.11", &servaddr.sin_addr);
	//int rc = inet_pton(AF_INET, "0.0.0.0", &servaddr.sin_addr);
	//printf("INADDR_ANY = %d\n", INADDR_ANY);
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	printf("servaddr.sin_addr.s_addr = %08X\n", servaddr.sin_addr.s_addr);
	//servaddr.sin_addr.s_addr = htonl(servaddr.sin_addr.s_addr); 
	printf("servaddr.sin_addr.s_addr = %08X\n", servaddr.sin_addr.s_addr);

	servaddr.sin_port = htons(SERV_PORT); 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	listen(listenfd, 20); 
	printf("Accepting connections...\n"); 

	while(1) 
	{
		struct sockaddr_in cliaddr; 
		socklen_t cliaddr_len = sizeof(cliaddr); 
		int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len); 
		char buf[MAXLINE] = {0};
		int n = read(connfd, buf, MAXLINE); 
		char client_ip_str[INET_ADDRSTRLEN] = {0};
		inet_ntop(AF_INET, &cliaddr.sin_addr, client_ip_str, sizeof(client_ip_str)), 
		printf("received from %s at PORT %d\n", client_ip_str, ntohs(cliaddr.sin_port)); 
		int i;
		for(i=0; i<n; i++)
			buf[i] = toupper(buf[i]); 
		write(connfd, buf, n); 
		close(connfd); 
	} 
}
