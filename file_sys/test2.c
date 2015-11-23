#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[] = {"tcp=127.0.0.1\
addr=2003\n"};
	char *name = strtok(buf, "=");
	printf("name = %s|\n", name);
	return 0;
}
