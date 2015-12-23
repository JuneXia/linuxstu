#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>

void main()
{
	struct hostent *host = gethostbyname("192.168.171.129");
	printf("host = %p\n", host);
	printf("host->h_addr = %p\n", host->h_addr);
//	printf("host->h_addr->sin_addr.sa_data = %p\n", host->h_addr->sin_addr.sa_data);
	printf("host->h_name = %s\n", host->h_name);
	printf("host->h_aliases = %p\n", host->h_aliases);
	printf("host->h_addrtype = %d\n", host->h_addrtype);
	printf("host->h_length = %d\n", host->h_length);

}
