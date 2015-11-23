#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // OK
pthread_mutex_t mutex;

void *doit1(void *);
void *doit2(void *);

int main()
{
	pthread_t tid1, tid2;
	pthread_mutex_init(&mutex, NULL); // OK

	pthread_create(&tid1, NULL, doit1, NULL);
	pthread_create(&tid2, NULL, doit2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_mutex_destroy(&mutex);

	return 0; 
}

void *doit1(void *vptr)
{
	printf("%x , doit1 waiting mutex!\n", (unsigned int)pthread_self());
	pthread_mutex_lock(&mutex); // if there is another thread to preempt the mutex lock, then the current thread will block here.
	printf("%x , doit1 get mutex!\n", (unsigned int)pthread_self());

	int i;
	for (i = 0; i < 5; i++)
	{
		printf("doit1 working on!\n");
		sleep(1);
	}
	pthread_mutex_destroy(&mutex);

	pthread_mutex_unlock(&mutex);
	printf("%x , doit1 released mutex!\n", (unsigned int)pthread_self());
	
	return NULL;
}

void *doit2(void *vptr)
{
	printf("%x , doit2 waiting mutex!\n", (unsigned int)pthread_self());
	pthread_mutex_lock(&mutex); // if there is another thread to preempt the mutex lock, then the current thread will block here.
	printf("%x , doit2 get mutex!\n", (unsigned int)pthread_self());

	int i;
	for (i = 0; i < 5; i++)
	{
		printf("doit2 working on!\n");
		sleep(1);
	}

	pthread_mutex_unlock(&mutex);
	printf("%x , doit2 released mutex!\n", (unsigned int)pthread_self());

	return NULL;
}
