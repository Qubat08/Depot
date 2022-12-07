#include <stdio.h>

int repre(int x){
	while (x>10){
		x=x/10;
	}
	return x;
}

int main(){
	int a;
	printf("Saisir valeur \n");
	scanf("%d",&a);

	printf("%d",repre(a));
}