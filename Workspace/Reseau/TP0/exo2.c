#include <stdio.h>
#include <stdlib.h>

int* extract(int* T, int n, int a, int b, int * ns){
	int j = 0;
	int k = 0;

	int* retour;

	for(j = 0 ; j < n ; j++){
		if(T[j] >= a && T[j] <= b){
			k++;
			
			retour = (int*) realloc(retour, k * sizeof(int));
			retour[k-1] = T[j];
		}
	}
	*ns = k;

	return retour;
}

int main(){
  	int t[] = {1,3,5,7,4,9,5,5,5,5,5,5,5,5,5,5};
	int n = 16;
	int a = 2;
	int b = 5;
	int taille;
	int i = 0;

	int* plop = extract(t, n, a, b, &taille);

	for(i = 0 ; i < taille ; ++i){
		printf("%d\n", plop[i]);
	}

	free(plop);	
  
  	return 0;
}
