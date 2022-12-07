#include <stdio.h>
#define T 100
void tri(int tab[],int N){
	int i=0,j=0,temp=0;

	for (i=0;i<N-1;i++){
		for (j=0;j<N-i-1;j++){
			if (tab[j]>tab[j+1]){
				temp = tab[j];
				tab[j]=tab[j+1];
				tab[j+1] = temp;
			}
		}
	}
}

int main(){
	int tab[T];
	int taille;
	int i;

	printf("Saisir taille \n");
	scanf("%d",&taille);

	for (i=0;i<taille;i++){
		printf("Saisir valeur de tab[%d] \n",i);
		scanf("%d",&tab[i]);
	}
	printf("\n");
	for (i=0;i<taille;i++){
		printf("%d ",tab[i]);
	}
	tri(tab,taille);

	printf("\n");
	for (i=0;i<taille;i++){
		printf("%d ",tab[i]);
	}

	return 0;
}