#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <errno.h> 
#include <sys/ipc.h> 
#include <semaphore.h> 

int lock_var; 
time_t end_time; 
sem_t sem; 
void pthread1(void *arg); 
void pthread2(void *arg); 
void pthread3(void *arg); 

int main(int argc, char *argv[]) 
{ 
	pthread_t id1, id2, id3; 
	pthread_t mon_th_id; 
	int ret; 
	end_time = time(NULL) + 30; 

	/*初始化信号量为1*/ 
	ret = sem_init(&sem, 0, 2); 
	if(ret!=0) 
	{ 
		perror("sem_init"); 
	} 

	/*创建两个线程*/ 
	ret = pthread_create(&id1, NULL, (void *)pthread1, NULL); 
	if(ret != 0) 
		perror("pthread cread1"); 
	ret = pthread_create(&id2, NULL, (void *)pthread2, NULL); 
	if(ret != 0) 
		perror("pthread cread2"); 
	ret = pthread_create(&id3, NULL, (void *)pthread3, NULL); 
	if(ret != 0) 
		perror("pthread cread3"); 

	pthread_join(id1, NULL); 
	pthread_join(id2, NULL); 
	pthread_join(id3, NULL); 

	ret = sem_destroy(&sem);
	if(ret != 0) 
		perror("sem_destroy"); 

	exit(0); 
} 

void pthread1(void *arg) 
{ 
	int i; 
	while(time(NULL) < end_time)
	{
		int semvalue = -1;
		sem_getvalue(&sem, &semvalue);
		printf("pthread1: before sem_wait, semvalue = %d\n", semvalue);

		/*信号量减一，P操作*/
		sem_wait(&sem);
		sem_getvalue(&sem, &semvalue);
		printf("pthread1: get lock, semvalue = %d\n", semvalue);
		for(i=0;i<2;i++)
		{
			sleep(1);
			lock_var++;
			printf("pthread1: lock_var = %d\n",lock_var);
		}

		/*信号量加一，V操作*/
		sem_post(&sem);
		sem_getvalue(&sem, &semvalue);
		printf("pthread1: release lock, semvalue = %d\n", semvalue);

		sleep(3);
	}
}

void pthread2(void *arg)
{
	int nolock=0; 
	int ret; 
	while(time(NULL) < end_time)
	{
		int semvalue = -1;
		sem_getvalue(&sem, &semvalue);
		printf("pthread2: before sem_wait, semvalue = %d\n", semvalue);

		/*信号量减一，P操作*/ 
		sem_wait(&sem); 
		sem_getvalue(&sem, &semvalue);
		printf("pthread2: get lock, semvalue = %d\n", semvalue);
		printf("pthread2: lock_var = %d\n",lock_var);

		/*信号量加一，V操作*/ 
		sem_post(&sem); 

		sem_getvalue(&sem, &semvalue);
		printf("pthread2: release lock, semvalue = %d\n", semvalue);

		sleep(3); 
	}
}

void pthread3(void *arg)
{
	int nolock=0;
	int ret;
	while(time(NULL) < end_time)
	{
		int semvalue = -1;
		sem_getvalue(&sem, &semvalue);
		printf("pthread3: before sem_wait, semvalue = %d\n", semvalue);

		/*信号量减一，P操作*/ 
		sem_wait(&sem); 
		sem_getvalue(&sem, &semvalue);
		printf("pthread3: get lock, semvalue = %d\n", semvalue);
		printf("pthread3: lock_var = %d\n",lock_var);

		/*信号量加一，V操作*/ 
		sem_post(&sem); 

		sem_getvalue(&sem, &semvalue);
		printf("pthread3: release lock, semvalue = %d\n", semvalue);

		sleep(3); 
	}
}
