#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_PATH "wsndaemon.conf"
/*
char ip[20] = {"127.0.0.1"};
int serverport = 2004;
int tcpserialport = 2003;
char *name;
char *value;
float version = 1.01;
*/
char ip[20] = {0};
int serverport = 0;
int tcpserialport = 0;
char *name = NULL;
char *value = NULL;
float version = 0.0f;

int main(void)
{
	FILE *fp_conf = NULL;
	int fd;
	char buf[100];
	char delim[] = "=";

	fd = open(FILE_PATH, O_RDONLY);
	printf("fd = %d\n", fd);
	if (fd < 0) {
		exit(1);
	}

	fp_conf = fdopen(fd, "r");
	if (fp_conf < 0) {
		printf("fp_conf < 0\n");
		exit(1);
	}

	while (1) {
		memset(buf, 0, 100);
		if (fgets(buf, 100, fp_conf) == NULL) {
			break;
		}
		printf("buf = %s\n", buf);
		name = strtok(buf, delim);
		value = strtok(NULL, delim);
		printf("name = %s\n", name);
		printf("value = %s\n", value);
		if (strncasecmp("tcpaddr", name, 7) == 0) {
			memcpy(ip, value, 20);
			printf("ip1 = %s\n", ip);
			int i;
			for (i = 0; i < 20; i++) {
				if (ip[i] == '\n')
					ip[i] = '\0';
			}
			printf("ip2 = %s\n", ip);
		} else if (strncasecmp("serverport", name, 10) == 0)
			serverport = atoi(value);
		else if (strncasecmp("tcpserialport", name, 13) == 0)
			tcpserialport = atoi(value);
		else
			version = atof(value);
		printf("value= %s\n", value);
		printf("serverportt= %d\n", serverport);
		printf("tcpserialport = %d\n", tcpserialport);
		printf("version = %f\n", version);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
	return 0;
}


