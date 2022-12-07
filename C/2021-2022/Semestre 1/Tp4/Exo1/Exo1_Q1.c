#include <stdio.h>
int main(){
char chaine[]= "Ceci est une chaine";
int i =0;
while(chaine[i]!='\0'){
	printf("%c \t",chaine[i]);
	i++;
}
return 0;
}