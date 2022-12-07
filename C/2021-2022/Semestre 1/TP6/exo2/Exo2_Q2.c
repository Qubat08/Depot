#include <stdio.h>

int estEgale(int a, int b, int c){
	if (a==b && b!=c){
		return 1;
	}
	else if (b==c && a!=b){
		return 1;
	}
	else if (a==c && b!=a){
		return 1;
	}
	else{
		return 0;
	}
}



int main(){

int a,b,c;
printf("Saisir valeur a,b,c\n");
scanf("%d %d %d",&a,&b,&c);


if (estEgale(a,b,c)){
	printf("\nVrai");
} else{
	printf("\nFaux");
}

return 0;
}