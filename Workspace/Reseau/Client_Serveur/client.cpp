#include "sock.h"
#include "sockdist.h"
#include <pwd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include<errno.h>




int main(int argc, char** argv){

    char message[1000];
	char recu[1000];
	int trecu;
	char adresse[20];

	/***********************************************************************
	1/choisir l adresse de connexion (adresse).
	***********************************************************************/

	std::cout <<"tapez l'adresse où se connecter"<< endl;
	std::cin.getline(adresse,1000);

	/***********************************************************************
	2/Definir BRLOCAL et adresse expedition
	***********************************************************************/
	SockDist Expd(adresse,31466);
	Sock BRlocal(SOCK_STREAM, 31467, 0);//pour autotest 31466/31467
	
	int destLocal = BRlocal.getsDesc();
	socklen_t taille=Expd.getsLen();

	sockaddr_in* adresseExp = Expd.getAdrDist();




/*BRLOCAL.good() avec getsDesc*/

	/***********************************************************************
	3/Demande de connexion au serveur
	***********************************************************************/
	int test = connect(destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));

        int tmp = getuid();
	sprintf(message,"%d",tmp);//convertir decimal en string

	cout <<tmp<<endl;


    	/***********************************************************************
	4/ Envoi message
	***********************************************************************/
	/*boucler tant qu on a pas entierement tout envoyé send(taille)*/
        int tmp1 = send(destLocal,message,sizeof(message),0);
/*tmp>0 c est bon -1 pb*/
	cout<<"envoi du message"<<strerror(errno)<<"("<<errno<<")"<<endl;

    	/***********************************************************************
	5/ Reception message
	***********************************************************************/
        int tmp2 = recv(destLocal, recu, trecu, 0);
	
	cout << recu << endl;
	cout<<"retour du message"<<strerror(errno)<<"("<<errno<<")"<<endl;

	/***********************************************************************
	6/ Ferme fd de la connexion
	   Ferme fd de la socket
	***********************************************************************/
	close(test);
	close(destLocal);
	return 0;
}
