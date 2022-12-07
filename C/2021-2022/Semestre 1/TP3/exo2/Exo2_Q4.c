#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define T 10
int main (){
int i,j,c,tab[T],x, binf=0,bsup=T-1,p=0,res=-1;

//génération tableau
srand(time(NULL));
printf("\n");
for (i=0;i<T;i++){
	tab[i] = rand()%100;
	printf("%d,",tab[i]);
}
printf("\n");

//trie tableau
for(i=0;i<T;i++){
    for(j=i+1;j<T;j++){
        if ( tab[i] > tab[j] ) {
            c = tab[i];
            tab[i] = tab[j];
            tab[j] = c;
        }
    }
    printf("%d,",tab[i]);
 }
//recherche dichotomique tableau 
printf("\n Saisir valeur recherché: \n");
scanf("%d",&x);
while(binf<=bsup && tab[p]!=x){
	p=(binf+bsup)/2;
	if (tab[p]==x){
	  res=p;
	}
	 if (tab[p]<x){
	 binf =p+1;
        }
        if (tab[p]>x){
        bsup = p-1;
        }
}
	if (tab[p]==x){
	  if (p==0){
	    res=0;
	   }
}

//vérification pour affichage
if (res==-1){
  printf("Non trouvé \n");
  }
else{
printf("Trouvé au rang %d \n",res);
}



return 0;
}
