#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd = open("file", O_RDONLY | O_CREAT, S_IRUSR);
	int rev = -1;
	struct stat st;
	if (fd < 0)
	{
		perror("open error");
		exit(1);
	}
	
	rev = stat("file", &st);
	printf("stat rev = %d\n", rev);
	printf("st_dev = %ld\n", st.st_dev);
	printf("~~~~~~~~~~~~~~~~~~~~~~\n");

	rev = access("file", F_OK);
	printf("access rev = %d\n", rev);
	
	return 1;
}
