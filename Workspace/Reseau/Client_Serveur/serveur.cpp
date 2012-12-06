#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>

#include "sock.h"
#include "sockdist.h"

int main(int argc, char** argv){
  char envoi[1000];
	char recu[1000];
	int trecu;
	/***********************************************************************
	1/Definir BRLOCAL et adresse expedition
	***********************************************************************/
	SockDist Expd("0",31466);// pour autotest 31466/31467
	Sock BRlocal(SOCK_STREAM, 31467, 0);
	int destLocal = BRlocal.getsDesc();
	socklen_t taille=Expd.getsLen();

	sockaddr_in* adresseExp = Expd.getAdrDist();


	/***********************************************************************
	2/Ouvre la liste d attente
	***********************************************************************/
	listen(destLocal, 2);
	cout<<"Mise en place Listen"<<strerror(errno)<<"("<<errno<<")"<<endl;
	cout << "Serveur a l'ecoute...\n\n";

	int tp;int tmp2;


	char debutTrait[1];
	cout<<"tapez ok et validez pour commencer le traitement";
	cin >> debutTrait;

	while(1){
	/***********************************************************************
	3/ Accept: traite premiere demande de file d attente s il y en a une
	***********************************************************************/
		tp = accept(destLocal,(struct sockaddr *) adresseExp,&taille);
		cout<<"Mise en place du accept"<<strerror(errno)<<"("<<errno<<")"<<endl;
		
		close(destLocal);//vu que copie du pere il a deja destlocal dans tp

		// Reception du message
				tmp2 = recv(tp,recu, trecu, 0);
			cout<<"Reception"<<strerror(errno)<<"("<<errno<<")"<<endl;

		cout << "Message recu : " << recu << endl;
		int a = atoi(recu);

		passwd* pwuid = getpwuid((uid_t)a);

		cout << " machine : " << pwuid->pw_name << endl;

		sprintf(envoi,"Tiens bonjour, %s",pwuid->pw_name);

			// Envoi du message
			int tmp1 = send(tp,envoi,sizeof(envoi),0);
		cout<<"Envoi"<<strerror(errno)<<"("<<errno<<")"<<endl;

		close(tp);
		break;
	}
	return 0;
}
