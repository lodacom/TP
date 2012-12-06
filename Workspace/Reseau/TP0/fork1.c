#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int nbFils = 5;
	int pid = getpid();

	while(nbFils != 0)
    {
		if(pid != 0)//donc c'est le père qui exécutera ci-dessous
        {
			pid = fork();//on crée autant de fils que l'on en a besoin
            sleep(10);
		}
		nbFils--;
	}


	if(pid == 0)
    {
		printf("je suis le fils %d du pere %d\n", getpid(), getppid());
	}
    else
    {
		wait(0);//le père attend les fils
        //le père prend la valeur du pid du fils
		printf("Je suis pere %d\n", getpid());
	}
	return 0;
}
