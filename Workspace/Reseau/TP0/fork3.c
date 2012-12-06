#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int hauteur = 3;
	int pid = 0;
	int nbFils;

	while(hauteur != 0)
    {
		if(pid == 0)
        {
            //au premier tour on va créer fils (à partir du père)
			pid = fork();//le père va prendre le pid du fils donc !=0 
			if(pid != 0)
            {
				pid = fork();//on crée un autre fils
			}
            //on se retrouve avec deux fils pid=0
		}
		hauteur--;
	}
	
	sleep(7);
	while(wait(0) != -1);
	printf("Je suis proc %d fils de %d\n", getpid(), getppid());
	

	return 0;
}
