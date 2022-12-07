#include <stdio.h>

void echange(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(){
	int x,y;
	printf("Saisir valeurs \n");
	scanf("%d %d", &x, &y);
	printf("\n Avant échange: x = %d et y = %d",x,y);
	echange(&x,&y);

	printf("\n Après échange: x = %d et y = %d \n",x,y);
	return 0;
}