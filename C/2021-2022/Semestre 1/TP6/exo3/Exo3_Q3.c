#include <stdio.h>

void plus5(int *a, int *b, int *c){
	*a+=5;
	*b+=5;
	*c+=5;
}



int main(){
	int a,b,c;
	printf("Saisir valeurs \n");
	scanf("%d %d %d",&a,&b,&c);


	printf("Avant modif a = %d b = %d c = %d \n",a,b,c);
	plus5(&a,&b,&c);

	printf("Après modif a = %d b = %d c = %d",a,b,c);

	return 0;
}