#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("argc = %d\n", argc);
	int i = 0;
	for (; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
}
