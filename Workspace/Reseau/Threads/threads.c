/*
 * threads.c
 *
 *  Created on: 6 nov. 2012
 *      Author: Lolo
 */
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* fct(void* p)
{
	int i;
	for (i=0;i<=20;i++)
	{
		printf("Thread secondaire\n");
		sleep(2);
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
	pthread_t id;
	pthread_create(&id,NULL,fct,NULL);
	int i;
	for (i=0;i<=10;i++)
	{
		printf("Thread principal\n");
		sleep(2);
	}
	pthread_join(id,NULL);

	return 1;
}

