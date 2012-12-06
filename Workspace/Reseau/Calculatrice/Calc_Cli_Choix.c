/*
 * Calc_Cli_Choix.c
 *
 *  Created on: 6 oct. 2012
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
    	printf("Saisissez votre op�ration (op1 op2 operande):\n");
    	scanf("%lf",&MsgReqCli.operateur1);
    	scanf("%lf",&MsgReqCli.operateur2);

    	printf("\n");
    	CLEAR_STDIN
    	MsgReqCli.operande=getchar();
    	printf("%c",MsgReqCli.operande);

    	switch (MsgReqCli.operande)
    	{
		case '+':
			MsgReqCli.etiquette_snd=1;
			break;
		case '-':
			MsgReqCli.etiquette_snd=2;
			break;
		case '*':
			MsgReqCli.etiquette_snd=3;
			break;
		case '/':
			MsgReqCli.etiquette_snd=4;
			break;
		default:
			printf("Impossible d'envoyer l'op�ration demand�e\n");
			break;
    	}
		MsgReqCli.pid=getpid();
		//..................................................................................
		//Envoi de la requ�te
		int snd=msgsnd(id_file_rec, &MsgReqCli,sizeof(MsgReqCli)-sizeof(long),0);
		if (snd!=-1)
		{
			printf("Requ�te envoy�e avec pid: %d!!\n",MsgReqCli.pid);
		}
		else
		{
			printf("Erreur d'envoie!!\n");
		}
		//..................................................................................
		//R�cup�ration du traitement (de la r�ponse)
		int rcv=(int)msgrcv(id_file_rec, &MsgRepCli, sizeof(MsgRepCli)-sizeof(long), MsgReqCli.pid, 0);
		//On r�ceptionne sur le pid
		if (rcv!=-1)
		{
			printf("R�ponse re�ue!!\n");
			printf("L'op�ration donne: %lf\n", MsgRepCli.operation);
		}
		else
		{
			printf("Erreur de r�ception\n");
		}

		printf("Voulez-vous continuez?(o|n)\n");
		//fpurge(stdin);
		CLEAR_STDIN
		contin=getc(stdin);
    }
}

int main(int argc, const char * argv[])
{
    Recup_File_Cli();
    return 0;
}

