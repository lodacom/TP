/*
 * Decomposeur.c
 *
 *  Created on: 7 oct. 2012
 *      Author: Lolo
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define CLEAR_STDIN {int c; while((c = getchar()) && (c != '\n'));}

struct MsgReqCli {
	long etiquette_snd;
	int pid;
	int nbrentier;//le tableau de calcul pour les fils
} MsgReqCli;

int id_file_rec;
int tableau[100];
int nbdepart;
int res=1;

void Recup_File_Cli()
{
	key_t sesame = ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
	id_file_rec = msgget(sesame, IPC_CREAT|0666);
}

void InitTableau()
{
	int i;
	for (i=0;i<100;i++)
	{
		tableau[i]=0;
	}
}

void Engendre(int nbFils)
{
	int pid = getpid();

	while (nbFils != 0)
	{
		if (pid != 0) //donc c'est le p�re qui ex�cutera ci-dessous
		{
			pid = fork(); //on cr�e autant de fils que l'on en a besoin
		}
		nbFils--;
	}

	if (pid == 0)
	{
		printf("Traitement du calcul\n");
		//R�cup�ration et traitement
		while (res!=nbdepart)
		{
			int rcv = (int) msgrcv(id_file_rec, &MsgReqCli, sizeof(MsgReqCli)-sizeof(long),3, 0);
			//On r�ceptionne sur le pid
			if (rcv != -1)
			{
				printf("R�ponse re�ue!!\n");
				int i;

				int recup = MsgReqCli.nbrentier;
				printf("Nb re�u: %d\n",recup);
				int fact1 = 0, fact2 = 0;
				int j;
				for (j = 2; j <= recup-1; j++)
				{
					if ((recup % j) == 0 && (recup / j) > fact1)
					{
						fact1 = recup / j;
						fact2 = j;
					}
				}
				printf("Fact1: %d, fact2: %d\n",fact1,fact2);
				if (fact1 != 0)
				{
					//on a trouv� deux facteurs
					MsgReqCli.pid=getpid();
					MsgReqCli.etiquette_snd = 3; //on doit continuer le calcul
					//on envoi sur le fils suivant
					MsgReqCli.nbrentier=fact1;//envoie du premier facteur
					//Envoi aux fils suivants
					int snd1_fils = msgsnd(id_file_rec, &MsgReqCli,sizeof(MsgReqCli) - sizeof(long), 0);
					if (snd1_fils!=-1)
					{
						printf("Premier envoie\n");
					}
					else
					{
						printf("Erreur d'envoie\n");
						printf("%s",strerror(errno));
					}

					//on a trouv� deux facteurs
					MsgReqCli.pid=getpid();
					MsgReqCli.etiquette_snd = 3; //on doit continuer le calcul
					//on envoi sur le fils suivant
					MsgReqCli.nbrentier=fact2;//envoie du deuxi�me facteur
					//Envoi aux fils suivants
					int snd2_fils = msgsnd(id_file_rec, &MsgReqCli,sizeof(MsgReqCli) - sizeof(long), 0);
					if (snd2_fils!=-1)
					{
						printf("Deuxi�me envoie\n");
					}
					else
					{
						printf("Erreur d'envoie\n");
						printf("%s",strerror(errno));
					}
				}
				//..................................................................................
				else
				{
					MsgReqCli.etiquette_snd = 2; //envoi au parent
					MsgReqCli.pid=getpid();
					MsgReqCli.nbrentier=recup;
					//Envoi au p�re
					int snd_pere = msgsnd(id_file_rec, &MsgReqCli, sizeof(MsgReqCli)-sizeof(long), 0);
					if(snd_pere!=-1)
					{
						printf("Envoie du nombre premier au p�re\n");
					}
					else
					{
						printf("Erreur d'envoie au p�re\n");
						printf("%s",strerror(errno));
					}
				}
			}
			else
			{
				printf("Erreur de r�ception ou refus du serveur\n");
				printf("%s",strerror(errno));
			}

		}
	}
	else
	{
		//Envoi de la requ�te par le parent
		srand(time(NULL ));
		MsgReqCli.nbrentier = rand()%10000;
		nbdepart=MsgReqCli.nbrentier;

		printf("Nombre choisi: %d\n",MsgReqCli.nbrentier);

		MsgReqCli.etiquette_snd = 3;//sur les fils
		MsgReqCli.pid = getpid();
		int num_pere= MsgReqCli.pid;

		int snd = msgsnd(id_file_rec, &MsgReqCli, sizeof(MsgReqCli) - sizeof(long), 0);
		if (snd != -1)
		{
			printf("Requ�te envoy�e par le p�re\n");
		}
		else
		{
			printf("Erreur d'envoie lol!!\n");
			printf("%s",strerror(errno));
		}


		while (res!=nbdepart)
		{
			int rcv = msgrcv(id_file_rec, &MsgReqCli, sizeof(MsgReqCli) - sizeof(long), 2, 0);
			if (rcv==-1)
			{
				printf("Erreur de r�ception du p�re\n");
			}
			else
			{
				printf("R�ception r�ussie du p�re\n");
			}

			int recup=MsgReqCli.nbrentier;
			printf("Nombre premier: %d\n",recup);
			int i=0;
			while (i<100 && tableau[i]!=0)
			{
				i++;
			}
			tableau[i]=recup;
			res=res*recup;
		}

		int k;
		for (k=0;k<100;k++)
		{
			printf("%d,",tableau[k]);
		}

	}
		//le p�re attend les fils
		//le p�re prend la valeur du pid du fils

}


int main(int argc, const char * argv[])
{
	InitTableau();
	Recup_File_Cli();
	int nbrfils;
	printf("Saisissez le nombre de fils\n");
	scanf("%d",&nbrfils);

	Engendre(nbrfils);
	return 0;
}

