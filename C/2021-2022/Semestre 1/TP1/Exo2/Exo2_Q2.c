#include <stdio.h>
int main(){/* Déclaration des variables*/
int a =10, b=010, c=0x10,d;

printf("a en décimal = %d, a en octal = %o et a en hexa = %x \n",a,a,a);
printf("b en décimal = %d, b en octal = %o et b en hexa = %x \n",b,b,b);
printf("c en décimal = %d, c en octal = %o et c en hexa = %x \n",c,c,c);

d = a*b;
printf ("d en décimal = %d, d en octal = %o et c en hexa = %x \n",d,d,d);
return 0;
}
