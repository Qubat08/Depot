#include <stdio.h>
#define T 100
int main (){
int n, tab[T],i;

do{
printf("Saisir Taille tableau: \n");
scanf("%d",&n);
}while(n<0 || n>100);

printf("Saisir valeur: \n");
for (i=0; i<n;i++){ 
 scanf("%d",&tab[i]);
}
printf("\nNombre pair \n");
for (i=0; i<n; i++){
 	if (tab[i]%2 ==0){
  	 printf("\n%d \n",tab[i]);
  	}
}

return 0;
}
