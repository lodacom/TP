#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int nbFils = 5;
	int pid = 0;

	while(nbFils != 0)
    {
		if(pid == 0)//donc c'est le fils qui exécutera ci-dessous
        {
			pid = fork();
            sleep(10);
		}
		nbFils--;
	}


	if(pid == 0)
    {
		printf("je suis le bebe processus %d, mon pere est %d\n", getpid(), getppid());
	}
    else
    {
		wait(0);
		printf("Je suis proc %d fils de %d\n", getpid(), getppid());
	}
	return 0;
}
