#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define T 100
int main (){
int x,i,tab[T],test;
test =0;
srand(time(NULL));

for (i=0;i<T;i++){
	tab[i] = rand()%100;
	//printf("%d",tab[i]);
}


do{
printf("\nSaisir valeur recherchée [0, 100]: \n");
scanf("%d",&x);
}while(x<0 || x>100);


i=0;
while(test==0 && i<T){
 if (tab[i]==x){
  test = 1;
  }else{
   i++;
 }
}
if (i>T){
 i=-1;
}

printf("Trouvé au rang %d \n",i);


return 0;
}
