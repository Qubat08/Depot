#include <stdio.h>
#define T 100


int main(){

int cpt=0,i=0;
char chaine[T];int test;
int j;


scanf("%s",chaine);


for(j=(int)'0';j<(int)'9';++j){
	cpt=0;
for (i=0;chaine[i]!='\0';i++){
	if (j==(int)chaine[i]){
		cpt++;
	}
}
	printf("Le caractère %c apparait %d \n",j,cpt);
}



return 0;
}