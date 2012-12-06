/*
 * rdv.c
 *
 *  Created on: 6 nov. 2012
 *      Author: Lolo
 */
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/shm.h>

pthread_mutex_t verrou=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condi=PTHREAD_COND_INITIALIZER;
int nb_operation=4;

void* employe(void* p)
{
	key_t sesame=ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
	int id_shm=shmget(sesame,0,0444);//mémoire partagée

	printf("Dans employe\n");
	pthread_mutex_lock(&verrou);
	nb_operation--;
	if (nb_operation==0)
	{
		printf("Réveil du chef de service\n");
		//pthread_cond_signal(&condi);
		sleep(2);
		pthread_mutex_unlock(&verrou);
		pthread_exit(NULL);
	}
	else
	{
		char* msg=shmat(id_shm,NULL,0);
		printf("%s",msg);
		printf("\n");
		shmdt(msg);
		sleep(2);
	}
	pthread_mutex_unlock(&verrou);

	pthread_exit(NULL);
}

void* chef_service(void* p)
{
	pthread_mutex_lock(&verrou);
	key_t sesame=ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
	int id_shm=shmget(sesame,(size_t)256,IPC_CREAT|0644);//mémoire partagée

	char* msg=shmat(id_shm,NULL,0);
	strcat(msg,"Hello world!");
	int detach=shmdt(msg);
	sleep(2);
	pthread_mutex_unlock(&verrou);

	pthread_mutex_lock(&verrou);
	while (nb_operation!=0)
	{
		printf("Dans chef de service\n");
		sleep(2);
		pthread_cond_wait(&condi,&verrou);
		printf("Fin\n");
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&verrou);
	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
	pthread_t id_employe,id_chef;
	pthread_create(&id_chef,NULL,chef_service,NULL);
	int i;
	for(i=0;i<4;i++)
	{
		pthread_create(&id_employe,NULL,employe,NULL);
	}
	pthread_join(id_employe,NULL);
	pthread_join(id_chef,NULL);

	return 1;
}



