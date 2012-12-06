/* 
 * File:   main.c
 * Author: Lolo
 *
 * Created on 16 novembre 2012, 17:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//verrou pour attente de creation de T2
pthread_mutex_t verroux = PTHREAD_MUTEX_INITIALIZER;
int nbzone=4;
int peutlancerT2=0;

pthread_mutex_t tab[4];
int tabf[4]={0,1,2,3};

void* actionT1(void* p)
{
     printf("lancement T1 \n");
    int i;
    int j;
    for(i=0;i<nbzone;i++)
    {
        pthread_mutex_lock(&tab[i]);
        
    }
    pthread_mutex_lock(&verroux);
    peutlancerT2=1;
    pthread_mutex_unlock(&verroux);
    
    for(j=0; j<nbzone;j++)
    {
        tabf[j]++;
        printf("case %d T1: %d\n",j,tabf[j]);        
        pthread_mutex_unlock(&tab[j]);
        sleep(2);
    }
    pthread_exit(NULL);
}
void* actionT2(void* p)
{
    printf("lancement T2 \n");
    int j;
    for(j=0; j<nbzone;j++)
    {
        pthread_mutex_lock(&tab[j]);
        tabf[j]=tabf[j]*10;
        
        printf("case %d  T2: %d\n",j,tabf[j]);
        pthread_mutex_unlock(&tab[j]);
        //sleep(2);
    }  
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    
    pthread_t T1,T2;
    int i;
    for (i=0;i<nbzone;i++)
    {
    	pthread_mutex_init(&tab[i],NULL);
    }
    pthread_create(&T1,NULL,actionT1,NULL);
    pthread_mutex_lock(&verroux);//on bloque creation de T2
    
    while (peutlancerT2==0)
    {
        pthread_mutex_unlock(&verroux);
        sleep(2);
        pthread_mutex_lock(&verroux);
    }
    
    printf("creation T2 \n");
    pthread_mutex_unlock(&verroux);
    pthread_create(&T2,NULL,actionT2,NULL);
    
     pthread_join(T1,NULL);
     pthread_join(T2,NULL);

    return (EXIT_SUCCESS);
}

