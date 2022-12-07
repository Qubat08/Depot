#include <stdio.h>
#define T 100


void affichertab(int tab[],int n){
	int i;
	for (i=0;i<n;i++){
		printf("%d ",tab[i]);
	}
	printf("\n");
}

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

void IP(int A[],int P[],int I[], int N){
	int i=0;
	int j=0;
	int k=0;
	for (i=0;i<N;i++){
		if (A[i]%2 == 0){
			P[j]=A[i];
			j++;
		}
		else{
			I[k]=A[i];
			k++;
		}
	}

	tri(I,k);
	tri(P,j);
	printf("Impair: ");
	affichertab(I,k);
	printf("Pair: ");
	affichertab(P,j);

}



int main(){
	int A[T];
	int P[T];
	int I[T];
	int n,i;


	printf("Saisir taille \n");
	scanf("%d",&n);

	for (i=0;i<n;i++){
		printf("Saisir valeur de A[%d] \n",i);
		scanf("%d",&A[i]);
	}

	IP(A,P,I,n);


}