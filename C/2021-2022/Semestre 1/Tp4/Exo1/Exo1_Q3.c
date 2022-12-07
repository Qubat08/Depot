#include <stdio.h>

int main(){

int n=0,i=0;
char chaine[6]; 


do{
	printf("Saisir un entier strictement positif à 5 chiffres: \n");
	scanf("%d",&n);

}while(n<=9999 || n>=100000);



chaine[4]=n%10+'0';
n=n/10;
chaine[3]=n%10+'0';
n=n/10;
chaine[2]=n%10+'0';
n=n/10;
chaine[1]=n%10+'0';
n=n/10;
chaine[0]=n+'0';


/*for (i=5;i<=0;i++){
	chaine[i]=n%10+'0';
	n=n/10;
}*/

for (i=0;i<5;i++){
	printf("%c",chaine[i]);
}

printf("\n");
return 0;	
}