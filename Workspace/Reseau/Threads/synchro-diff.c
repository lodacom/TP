/* 
 * File:   main.c
 * Author: Lolo
 *
 * Created on 16 novembre 2012, 17:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/*
 * 
 */


//verrou pour attente de creation de T2
pthread_mutex_t verroux = PTHREAD_MUTEX_INITIALIZER;

int nbzone=4;
int peutlancerT2=0;
pthread_cond_t condition;




int tabf[4]={0,1,2,3};
int tabZAT[3]={-1,-1,-1};//autant de case de thread donc ici 3

void* actionT1(void* p)
{
    //int peutlibT2=((int*)p*);
     printf("lancement T1 \n");
    int i;
    int j;
    for(i=0;i<nbzone;i++)
    {
        pthread_mutex_lock(&verroux);
        tabZAT[0]++;//incremente la zone traiter par le thread (ici 0 correspond au thread 1)
        pthread_cond_broadcast(&condition);//condition est rempi
           
	   int k;
	   for(k=0;k<3;k++)
	   {
		   printf("thread %d: zone: %d\n",k,tabZAT[k]);
	   }

	   pthread_mutex_unlock(&verroux);
	   tabf[i]++;//traitement et affichge
	   sleep(2);
	   printf("case %d T1: %d\n",i,tabf[i]);

    }
    pthread_mutex_lock(&verroux);
    tabZAT[0]++;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&verroux);
   
        
    }
    

void* actionT2(void* p)
{
    printf("lancement T2 \n");
    int i;
    for(i=0;i<nbzone;i++)
    {
        pthread_mutex_lock(&verroux);
        tabZAT[1]++;//incremente la zone traiter par le thread (ici 1 correspond au thread 2)
         pthread_cond_broadcast(&condition);//condition est rempi
         while(i>=tabZAT[0])
         {//la zone traiter par le thread precedent
             pthread_cond_wait(&condition,&verroux);//attente
         }
         
         int k;
         for(k=0;k<3;k++)
         {
             printf("thread %d: zone: %d\n",k,tabZAT[k]);
         }

	   pthread_mutex_unlock(&verroux);

	   printf("T2 traite: %d\n",i);
	   tabf[i]=tabf[i]*10;//traitement et affichge
	   sleep(2);

    }
    
   pthread_mutex_lock(&verroux);
	  tabZAT[1]++;
	  pthread_cond_broadcast(&condition);

   pthread_mutex_unlock(&verroux);
}

void* actionT3(void* p){
    printf("lancement T3 \n");
      
    int i;
    for(i=0;i<nbzone;i++)
    {
        pthread_mutex_lock(&verroux);
        tabZAT[2]++;//incremente la zone traiter par le thread (ici 2 correspond au thread 3)
         pthread_cond_broadcast(&condition);//condition est rempi
         while(i>=tabZAT[1])
         {//la zone traiter par le thread precedent
             pthread_cond_wait(&condition,&verroux);
         }

         int k;
         for(k=0;k<3;k++){
             printf("thread %d: zone: %d\n",k,tabZAT[k]);
         }

           pthread_mutex_unlock(&verroux);
           
           tabf[i]=tabf[i]+1000;//traitement et affichge
           sleep(2);
           printf("case %d T3: %d\n",i,tabf[i]);
        
    }
    
	  pthread_mutex_lock(&verroux);
	  tabZAT[2]++;
	  pthread_cond_broadcast(&condition);

           pthread_mutex_unlock(&verroux);

}

int main(int argc, char** argv) {
    
    pthread_t T1,T2,T3;

    
    pthread_cond_init(&condition,NULL);
    int k;
      for(k=0;k<3;k++){
               printf("thread %d: zone: %d\n",k,tabZAT[k]);
           }
    
    pthread_create(&T1,NULL,actionT1,NULL);
    pthread_create(&T2,NULL,actionT2,NULL);
    pthread_create(&T3,NULL,actionT3,NULL);
    
     pthread_join(T1,NULL);
     pthread_join(T2,NULL);
     pthread_join(T3,NULL);
    return (EXIT_SUCCESS);
}

