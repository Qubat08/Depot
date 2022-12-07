#include <stdio.h>

int max(int a, int b, int c){
	int max = a;
	if (max <b){
		max = b;
	}
	if (max<c){
		max = c;
	}
	return max;
}

int main(){
int a,b,c;
printf("Saisir valeur a,b,c\n");
scanf("%d %d %d",&a,&b,&c);

printf("\nLa valeur max est %d\n",max(a,b,c));



return 0;
}