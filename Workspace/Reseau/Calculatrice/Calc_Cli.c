/*
 * Calc_Cli.c
 *
 *  Created on: 4 oct. 2012
 *      Author: Lolo
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

#define CLEAR_STDIN {int c; while((c = getchar()) && (c != '\n'));}

struct MsgReqCli
{
    long etiquette_snd;
    int pid;
    double operateur1;
    double operateur2;
    char operande;
}MsgReqCli;


struct MsgRepCli
{
    long etiquette_rcv;
    double operation;
}
MsgRepCli;

void Recup_File_Cli()
{
	char contin='o';

    key_t sesame=ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
    int id_file_rec=msgget(sesame,0666);

    while (contin=='o')
    {
    	printf("Saisissez votre opération (op1 op2 operande):\n");
    	scanf("%lf",&MsgReqCli.operateur1);
    	scanf("%lf",&MsgReqCli.operateur2);

    	//fpurge(stdin);

    	//printf("\n");
    	CLEAR_STDIN
    	MsgReqCli.operande=getc(stdin);


		MsgReqCli.etiquette_snd=10;//intialisation de l'étiquette en dur
		MsgReqCli.pid=getpid();

		//printf("%lf %c %lf",MsgReqCli.operateur1,MsgReqCli.operande,MsgReqCli.operateur2);
		//..................................................................................
		//Envoi de la requête
		int snd=msgsnd(id_file_rec, &MsgReqCli,sizeof(MsgReqCli)-sizeof(long),0);
		if (snd!=-1)
		{
			printf("Requête envoyée avec pid: %d!!\n",MsgReqCli.pid);
		}
		else
		{
			printf("Erreur d'envoie!!\n");
		}
		//..................................................................................
		//Récupération du traitement (de la réponse)
		int rcv=(int)msgrcv(id_file_rec, &MsgRepCli, sizeof(MsgRepCli)-sizeof(long), MsgReqCli.pid, 0);
		//On réceptionne sur le pid
		if (rcv!=-1)
		{
			printf("Réponse reçue!!\n");
			printf("L'opération donne: %lf\n", MsgRepCli.operation);
		}
		else
		{
			printf("Erreur de réception\n");
		}

		printf("Voulez-vous continuez?(o|n)\n");
		//fpurge(stdin);
		//printf("\n");
		CLEAR_STDIN
		contin=getc(stdin);
    }
}

int main(int argc, const char * argv[])
{
    Recup_File_Cli();
    return 0;
}

