/*
 * immatriculation.c
 *
 *  Created on: 6 nov. 2012
 *      Author: Lolo
 */
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

struct immat
{
	int chiffres[3];
	char lettres[3];
	int fixe[2];
}inter,m;

pthread_mutex_t verrou=PTHREAD_MUTEX_INITIALIZER;

void* fct(void* p)
{
	int nbimmat=0;
	while(nbimmat<10)
	{
		pthread_mutex_lock(&verrou);
		inter=m;

		if (m.chiffres[2]>8)
		{
			m.chiffres[2]=0;
			if(m.chiffres[1]>8)
			{
				m.chiffres[1]=0;
				if(m.chiffres[0]>8)
				{
					m.chiffres[0]=0;
				}
				else
				{
					m.chiffres[0]++;
				}
			}
			else
			{
				m.chiffres[1]++;
			}
		}
		else
		{
			m.chiffres[2]++;
		}

		if (m.lettres[2]>'y')
		{
			m.lettres[2]='a';
			if(m.lettres[1]>'y')
			{
				m.lettres[1]='a';
				if(m.lettres[0]>'y')
				{
					m.lettres[0]='a';
				}
				else
				{
					m.lettres[0]++;
				}
			}
			else
			{
				m.lettres[1]++;
			}
		}
		else
		{
			m.lettres[2]++;
		}
		sleep(5);
		pthread_mutex_unlock(&verrou);
		printf("Votre voiture a été immatriculée:%d%d%d %c%c%c 34\n",inter.chiffres[0],inter.chiffres[1],
		inter.chiffres[2],inter.lettres[0],inter.lettres[1],inter.lettres[2]);
		nbimmat++;
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
	pthread_t id;
	m.chiffres[0]=0;
	m.chiffres[1]=0;
	m.chiffres[2]=0;

	m.lettres[0]='a';
	m.lettres[1]='a';
	m.lettres[2]='a';

	m.fixe[0]=3;
	m.fixe[1]=4;

	pthread_create(&id,NULL,fct,NULL);
	int i;
	for (i=0;i<=10;i++)
	{
		printf("Thread principal\n");
		sleep(2);
	}
	pthread_join(id,NULL);

	return 1;
}


