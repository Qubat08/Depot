#include <stdio.h>
int main(){

char c;
scanf("%c",&c);

if (c >=48 && c<=57){
	printf("\n Ceci est un chiffre \n");
	}
else if(c>=65 && c<= 90){
	//printf("\n Ceci est une lettre majuscule");
	if (c == 65 || c == 69 || c == 73 || c == 79 || c == 85 || c == 89){
	 printf("Voyelle majuscule \n");
	}
	else{
	 printf("Consonne majuscule \n");
	}	
    }
 else if (c>=97 && c<=122){
  //lettre minuscule
     if (c==97||c==101||c==105||c==111||c==117||c==121){
      printf("Voyelle minuscule\n");
     }
     else{
      printf("Consonne minuscule\n");
     }     
 }
  else{
	printf("Autre\n");
 }
return 0;
}
