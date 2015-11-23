#include <stdio.h>
#include <arpa/inet.h>

void main()
{
        struct in_addr addr;
        //int rc = inet_pton(AF_INET, "192.168.1.2", &addr);
        //int rc = inet_pton(AF_INET, "1.1.1.1", &addr);
        int rc = inet_pton(AF_INET, "0.0.0.1", &addr);
        //int rc = inet_aton("0.0.0.1", &addr);
        printf("rc = %d, addr = %08X\n", rc, addr.s_addr);

        char str[INET_ADDRSTRLEN] = {0};
        const char *s = inet_ntop(AF_INET, &addr, str, (socklen_t)sizeof(str));
        //const char *s = inet_ntoa(addr);
        printf("s = %p ---> %s, str = %p ---> %s\n", s, s, str, str);
}
