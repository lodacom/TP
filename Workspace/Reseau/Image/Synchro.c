/*
 * Synchro.c
 *
 *  Created on: 23 oct. 2012
 *      Author: Lolo
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>

int id_sem;
int id_shm;
struct sembuf sembuf;
union semun semun;

void Init(int n)
{
	key_t sesame = ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
    unsigned short values[n];
    int i;
    for (i=0;i<n;i++)
    {
    	values[i]=1;
    }
    semun.array=values;
    int id_sem=semget(sesame,n,IPC_CREAT|0666);//sŽmaphore
    int id_shm=shmget(sesame,(size_t)sizeof(int*),IPC_CREAT|0644);//mŽmoire partagŽe
}

void Engendre(int nbFils)
{
	int pid = getpid();

	while (nbFils != 0)
	{
		if (pid != 0) //donc c'est le pre qui exŽcutera ci-dessous
		{
			pid = fork(); //on crŽe autant de fils que l'on en a besoin
		}
		nbFils--;
	}

	if (pid == 0)
	{
		printf("Traitement du calcul\n");

		sembuf.sem_num=0;
		sembuf.sem_op=-1;
		sembuf.sem_flg=0;

		semop(id_sem,&sembuf,1);
		sleep(10);
		int* truc=shmat(id_shm,NULL,0);

		int detach=shmdt(truc);

		sembuf.sem_num=0;
		sembuf.sem_op=1;
		sembuf.sem_flg=0;

		semop(id_sem,&sembuf,1);
	}
	else
	{
		wait(0);
	}

}


int main(int argc, const char * argv[])
{
	Init(3);
	int nbrfils;
	printf("Saisissez le nombre de fils\n");
	scanf("%d",&nbrfils);

	Engendre(nbrfils);
	return 0;
}


