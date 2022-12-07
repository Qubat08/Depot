#include <stdio.h>
void somme(int *a, int *b){
	*a+=*b;
}

int main(){
	int a,b;
	printf("Saisir valeurs: \n");

	scanf("%d %d",&a,&b);

	somme(&a,&b);
	printf("%d \n",a);
	return 0;
}