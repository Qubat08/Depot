#include <stdio.h>
#define T 100
int main(){

char chaine1[T]; 
char chaine2[T];
int i,test=0,res=0;

printf("Saisir première chaine: ");
scanf("%s",chaine1);


printf("Saisir deuxième chaine2: ");
scanf("%s",chaine2);


while(chaine1[i]==chaine2[i] || test==0){
	if (chaine1[i]<chaine2[i]){
		res=1;
		test=1;
	}
	else{
		res=2;
		test=1;
	}
	i++;

}

if (res==1){
	printf("\n %s \n %s \n",chaine1,chaine2);
} else{
	printf("\n %s \n %s \n",chaine2,chaine1);
}





return 0;	
}