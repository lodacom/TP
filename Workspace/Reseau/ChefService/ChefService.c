/*
 * ChefService.c
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

#define CLEAR_STDIN {int c; while((c = getchar()) && (c != '\n'));}

struct sembuf sembuf;
union semun semun;

void ChefService(int n)
{
    key_t sesame=ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
    char ferme='n';
    unsigned short values[2];
    values[0]=1;
    values[1]=n;
    semun.array=values;//mutex + nombre d'employés voir paramètre

    //......................................................
    int id_shm=shmget(sesame,(size_t)256,IPC_CREAT|0644);//mémoire partagée
    int id_sem=semget(sesame,2,IPC_CREAT|0666);//sémaphore

    int init=semctl(id_sem,2,SETALL,semun.array);//initialisation sémaphores
    if (init==0)
    {
    	printf("Initialisation des sémaphores réussis\n");
    }
    else
    {
    	printf("Erreur d'initialisation\n");
    }
    //......................................................
    while(ferme!='o')
    {
		sembuf.sem_num=0;
		sembuf.sem_op=-1;
		sembuf.sem_flg=0;

		semop(id_sem,&sembuf,1);//P1(S0)

		char* msg=shmat(id_shm,NULL,0);
		if (msg!=NULL)
		{
			printf("Attachement à la mémoire réussi\n");
		}
		else
		{
			printf("Erreur d'attachement\n");
		}
		//printf("Saisissez le message que vous voulez transmettre aux employes\n");
		//scanf("%s\n",msg);
		strcat(msg,"Hello world!");
		/*int i;
		for (i=0;i<10;i++)
		{
			msg[i]='a';
		}
		msg[i]='\0';*/

		int detach=shmdt(msg);
		if (detach==-1)
		{
			printf("Erreur de détachement\n");
		}
		else
		{
			printf("Détachement réussi\n");
		}

		sembuf.sem_num=0;
		sembuf.sem_op=1;
		sembuf.sem_flg=0;

		semop(id_sem,&sembuf,1);//V1(S0)

		struct sembuf op[]=
		{
			{1,0,0},
			{1,n,0}
		};
		semop(id_sem,op,2);//Z(S1)+Vn(S1)

		printf ("Voulez-vous fermer le serveur?(n|o)\n");

		printf("\n");
		CLEAR_STDIN
		ferme=getc(stdin);
    }
    //......................................................
}

int main(int argc, const char * argv[])
{
	int nbr_employe=0;
	printf("Saisissez le nombre d'employe auxquels vous voulez transmettre le message\n");
	scanf("%d\n",&nbr_employe);

    ChefService(nbr_employe);
    return 0;
}
