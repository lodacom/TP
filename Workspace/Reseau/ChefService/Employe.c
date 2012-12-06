/*
 * Employe.c
 *
 *  Created on: 11 oct. 2012
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

struct sembuf sembuf;
union semun semun;


void Employe()
{
    key_t sesame=ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
    char ferme='o';
    //......................................................
    int id_shm=shmget(sesame,0,0444);//mémoire partagée
    int id_sem=semget(sesame,2,0666);//sémaphore
    //......................................................
	sembuf.sem_num=0;
	sembuf.sem_op=-1;
	sembuf.sem_flg=0;

	semop(id_sem,&sembuf,1);//P1(S0)

	char* msg=shmat(id_shm,NULL,0);

	int i;
	for (i=0;msg[i]!='\0';i++)
	{
		printf("%c",msg[i]);
	}
	//printf("Message: %s\n",msg);

	shmdt(msg);

	sembuf.sem_num=0;
	sembuf.sem_op=1;
	sembuf.sem_flg=0;

	semop(id_sem,&sembuf,1);//V1(S0)

	sembuf.sem_num=1;
	sembuf.sem_op=-1;
	sembuf.sem_flg=0;
	semop(id_sem,&sembuf,1);//P1(S1)
    //......................................................
}

int main(int argc, const char * argv[])
{
    Employe();
    return 0;
}

