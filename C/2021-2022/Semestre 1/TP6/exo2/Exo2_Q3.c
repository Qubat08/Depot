#include <stdio.h>
#include <math.h>
int puisup(int n){
	int a =1,cpt=0;
	while(a<n){
		a*=2;
		cpt++;
	}
	return cpt;
}

int main(){
int a;
double b;
printf("Saisir valeur \n");
scanf("%d",&a);

printf("La plus grande puissance sup ou égale est: %d \n",puisup(a));

return 0;
}