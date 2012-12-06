/*
 * Calc_Serv_Choix.c
 *
 *  Created on: 6 oct. 2012
 *      Author: Lolo
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define CLEAR_STDIN {int c; while((c = getchar()) && (c != '\n'));}

struct MsgReq
{
    long etiquette_snd;
    int pid;
    double operateur1;
    double operateur2;
    char operande;
}MsgReq;


struct MsgRep
{
    long etiquette_rcv;
    double operation;
}
MsgRep;

void Recup_File_Serv()
{
	char ferme='n';
    double resultat;
    key_t sesame=ftok("~/Documents/TP/Workspace/Reseau/rien.txt", 10);
    int id_file=msgget(sesame,IPC_CREAT|0666);
    if (id_file!=-1)
    {
    	printf("Lancement du serveur de calculatrice\n");
    }
    else
    {
    	printf("Erreur de lancement\n");
    }

    while (ferme!='o')
    {
		//..................................................................................
		//Reception et traitement de la requête
		int rcv=(int)msgrcv(id_file, &MsgReq, sizeof(MsgReq)-sizeof(long), 0, 0);
		if (rcv!=-1)
		{
			printf("Réponse reçue avec l'envoyeur de pid: %d!!\n",MsgReq.pid);
			printf("%c\n",MsgReq.operande);
			switch (MsgReq.etiquette_snd) {
				case 1:
					resultat=MsgReq.operateur1+MsgReq.operateur2;
					break;
				case 2:
					resultat=MsgReq.operateur1-MsgReq.operateur2;
					break;
				case 3:
					resultat=MsgReq.operateur1*MsgReq.operateur2;
					break;
				case 4:
					resultat=MsgReq.operateur1/MsgReq.operateur2;
					break;
				default:
					resultat=-777;//nombre du diable ;)
					break;
			}
			MsgRep.operation=resultat;
		}
		else
		{
			printf("Erreur de réception\n");
		}
		//..................................................................................
		//Envoie de la réponse
		MsgRep.etiquette_rcv=MsgReq.pid;

		int snd=msgsnd(id_file, &MsgRep,sizeof(MsgRep)-sizeof(long),0);
		//on renvoie sur le pid, qui est contenu dans la structure
		if (snd!=-1)
		{
			printf("Requête envoyée!!\n");
		}
		else
		{
			printf("Erreur d'envoie!!\n");
			printf("%s\n", strerror(errno));
		}

		printf ("Voulez-vous fermer le serveur?(n|o)\n");

		printf("\n");
		CLEAR_STDIN
		ferme=getc(stdin);
    }

    int close=msgctl(id_file,IPC_RMID,NULL);
    if (close==0)
    {
    	printf("Fermeture du serveur de calculatrice\n");
    }
    else
    {
    	printf("Erreur de fermeture du serveur\n");
    }
}

int main(int argc, const char * argv[])
{
    Recup_File_Serv();
    return 0;
}

