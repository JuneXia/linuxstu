#include <stdio.h> 
#include <arpa/inet.h> 

void main()
{
	uint32_t net_long = htonl(1); 
	printf("net_long = %X\n", net_long);
	uint16_t net_short = htons(1); 
	printf("net_short = %X\n", net_short);

	uint32_t host_long = ntohl(net_long); 
	printf("host_long = %X\n", host_long);
	uint16_t host_short = ntohs(net_short); 
	printf("host_short = %X\n", host_short);
}
