#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *doit1(void *);
void *doit2(void *);

int main()
{
        pthread_t tid1, tid2;

        pthread_create(&tid1, NULL, doit1, NULL);
        pthread_create(&tid2, NULL, doit2, NULL);

	int *recv = NULL;
	printf("main(), &recv = %p, recv = %p\n", &recv, recv);
        
	printf("pthread1 join\n");
        pthread_join(tid1, (void **)&recv);
	printf("main(), &recv = %p, recv = %p, *recv = %d\n", &recv, recv, *recv);

	printf("pthread2 join\n");
        pthread_join(tid2, NULL);

	printf("main will return\n");
        return 0;
}

void *doit1(void *vptr)
{
	int i;
	int *recv = NULL;
        for (i = 0; i < 10; i++)
        {
                printf("pthread1 working on, i = %d!\n", i);
                sleep(1);
		if (i == 3)
		{
			int *send = (int *)malloc(sizeof(int));
			*send = 15;
			recv = send;
			printf("pthread1, &send = %p, send = %p, *send = %d\n", &send, send, *send);

			printf("pthread1 will call exit\n");
			pthread_exit(send);
			//break;
			//exit(1);
			printf("pthread1 finish call exit\n");
		}
        }
	printf("pthread1 will return\n");
        return recv;
}

void *doit2(void *vptr)
{
        int i;
        for (i = 0; i < 10; i++)
        {
                printf("pthread2 working on, i = %d!\n", i);
                sleep(1);
        }
        return NULL;
}
