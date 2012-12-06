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
		if (pid != 0) //donc c'est le père qui exécutera ci-dessous
		{
			pid = fork(); //on crée autant de fils que l'on en a besoin
		}
		nbFils--;
	}

	if (pid == 0)
	{
		printf("Traitement du calcul\n");
		//Récupération et traitement
		while (res!=nbdepart)
		{
			int rcv = (int) msgrcv(id_file_rec, &MsgReqCli, sizeof(MsgReqCli)-sizeof(long),3, 0);
			//On réceptionne sur le pid
			if (rcv != -1)
			{
				printf("Réponse reçue!!\n");
				int i;

				int recup = MsgReqCli.nbrentier;
				printf("Nb reçu: %d\n",recup);
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
					//on a trouvé deux facteurs
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

					//on a trouvé deux facteurs
					MsgReqCli.pid=getpid();
					MsgReqCli.etiquette_snd = 3; //on doit continuer le calcul
					//on envoi sur le fils suivant
					MsgReqCli.nbrentier=fact2;//envoie du deuxième facteur
					//Envoi aux fils suivants
					int snd2_fils = msgsnd(id_file_rec, &MsgReqCli,sizeof(MsgReqCli) - sizeof(long), 0);
					if (snd2_fils!=-1)
					{
						printf("Deuxième envoie\n");
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
					//Envoi au père
					int snd_pere = msgsnd(id_file_rec, &MsgReqCli, sizeof(MsgReqCli)-sizeof(long), 0);
					if(snd_pere!=-1)
					{
						printf("Envoie du nombre premier au père\n");
					}
					else
					{
						printf("Erreur d'envoie au père\n");
						printf("%s",strerror(errno));
					}
				}
			}
			else
			{
				printf("Erreur de réception ou refus du serveur\n");
				printf("%s",strerror(errno));
			}

		}
	}
	else
	{
		//Envoi de la requête par le parent
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
			printf("Requête envoyée par le père\n");
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
				printf("Erreur de réception du père\n");
			}
			else
			{
				printf("Réception réussie du père\n");
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
		//le père attend les fils
		//le père prend la valeur du pid du fils

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

