//阻塞读终端
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main1(void)
{
	char buf[10];
	int n;
	n = read(STDIN_FILENO, buf, 10);
	printf("|n = %d\n|", n);
	if (n < 0) 
	{
		perror("read STDIN_FILENO");
		exit(1);
	}
	write(STDOUT_FILENO, buf, n);
	return 0;
}


// 阻塞读终端
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(void)
{
	char buf[10];
	int fd, n;
	fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);
	if (fd < 0)
	{
		perror("open /dev/tty");
		exit(1);
	}

tryagain:
	n = read(fd, buf, 10);
	if (n < 0)
	{
		if (errno == EAGAIN)
		{
			sleep(1);
			write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
			goto tryagain;
		}
		perror("read /dev/tty");
		exit(1);
	}
	write(STDOUT_FILENO, buf, n);
	close(fd);
	return 0;
}

