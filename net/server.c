/*server.c*/ 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <unistd.h> 
#include <netinet/in.h> 

#define SERVPORT 3333 
#define BACKLOG 10 
#define MAX_CONNECTED_NO 10 
#define MAXDATASIZE 5 

void main()
{
	uint32_t net_long = htonl(1); 
	printf("net_long = %X\n", net_long);
	uint16_t net_short = htons(1); 
	printf("net_short = %X\n", net_short);

	//uint32_t host_long = ntohl(0x01000000); 
	uint32_t host_long = ntohl(net_long); 
	printf("host_long = %X\n", host_long);
	uint16_t host_short = ntohs(net_short); 
	printf("host_short = %X\n", host_short);
}
void main1()
{
	struct sockaddr_in sockaddr; 
	int sin_size,recvbytes; 
	int sockfd,client_fd; 
	char buf[MAXDATASIZE]; 

	sockaddr.sin_family=AF_INET; 
	sockaddr.sin_port=htons(SERVPORT); 
	sockaddr.sin_addr.s_addr=INADDR_ANY; 
	bzero(&(sockaddr.sin_zero),8); 
	printf("sockaddr.sin_port = %u\n", sockaddr.sin_port);
	printf("sockaddr.sin_addr.s_addr = %d\n", sockaddr.sin_addr.s_addr);

	//char addrptr[1024] = {0};
	struct in_addr addrptr;
	int rc = inet_pton(AF_INET, "127.0.0.1", &addrptr);
	printf("rc = %d, addrptr = |%d|\n", rc, addrptr.s_addr);

	//rc = inet_ntop(AF_INET, &addrptr.s_addr, "127.0.0.1", len);

/*
	struct in_addr addrptr2;
	int len = sizeof(addrptr2);
	rc = inet_ntop(AF_INET, &addrptr2, &addrptr.s_addr, len);
	printf("rc = %d, addrptr = |%d|\n", rc, addrptr2.s_addr);
	int i;
	for (i=0; i<sizeof(addrptr); i++)
	{
		//printf("%d  ", addrptr[i]);
	}
*/
	char addrptr2[1024] = {0};
	int len = sizeof(addrptr2);
	rc = inet_ntop(AF_INET, addrptr2, &addrptr.s_addr, len);
	printf("rc = %d, addrptr = |%s|\n", rc, addrptr2);
	
	printf("\n");
}
