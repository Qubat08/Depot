#include <stdio.h>
int main(){/* Déclaration des variables*/
char a,b,c;
printf("\nMerci de saisir un premier caractère : ");
scanf ("%c",&a); 
scanf("%c",&c); 
// mise en place d'un buffer car sinon b prend \0 (caractère fin de chaine)
printf("Le caractère saisie est %c et son code ascii est %d \n",a,a);

printf("\nMerci de saisir un deuxième caractère : ");
scanf ("%c",&b);
printf("Le caractère saisie est %c et son code ascii est %d \n",b,b);


return 0;
}
