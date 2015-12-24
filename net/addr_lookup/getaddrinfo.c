// 嵌入式linux应用程序开发详解
/*getaddrinfo.c*/ 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 

int main() 
{ 
	struct addrinfo hints,*res=NULL; 
	int rc; 
	memset(&hints,0,sizeof(hints)); 

	/*设置addrinfo结构体中各参数*/ 
	hints.ai_family=PF_UNSPEC; 
	hints.ai_socktype=SOCK_DGRAM; 
	hints.ai_protocol=IPPROTO_UDP; 

	printf("hints.ai_flags = %d\n", hints.ai_flags);
	printf("hints.ai_family = %d\n", hints.ai_family);
	printf("hints.ai_socktype = %d\n", hints.ai_socktype);
	printf("hints.ai_protocol = %d\n", hints.ai_protocol);
	printf("hints.ai_addrlen = %d\n", hints.ai_addrlen);
	printf("hints.ai_addr = %p\n", hints.ai_addr);
	//printf("hints.ai_addr->sa_data = %s\n", hints.ai_addr->sa_data);
	printf("hints.ai_canonname = |%s|\n", hints.ai_canonname);
	printf("hints.ai_next = %p\n", hints.ai_next);

	/*调用getaddinfo 函数*/ 
	rc=getaddrinfo("127.0.0.1","123",&hints,&res);// 123 是什么？ 

	if (rc != 0)
	{
		perror("getaddrinfo");
		exit(1);
	}
	else 
	{
		printf("getaddrinfo success\n");
		printf("res->ai_flags = %d\n", res->ai_flags);
		printf("res->ai_family = %d\n", res->ai_family);
		printf("res->ai_socktype = %d\n", res->ai_socktype);
		printf("res->ai_protocol = %d\n", res->ai_protocol);
		printf("res->ai_addrlen = %d\n", res->ai_addrlen);
		printf("res->ai_addr = %p\n", res->ai_addr);
		//printf("res->ai_addr->sa_len = |%d|\n", res->ai_addr->sa_len);
		printf("res->ai_addr->sa_family = %d\n", res->ai_addr->sa_family);
		printf("res->ai_addr->sa_data = |%s|\n", res->ai_addr->sa_data);
		printf("res->ai_canonname = |%s|\n", res->ai_canonname);
		printf("res->ai_next = %p\n", res->ai_next);
	}
}
