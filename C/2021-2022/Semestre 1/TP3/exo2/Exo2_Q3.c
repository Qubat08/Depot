#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define T 10
int main (){
int x,i,tab1[T],tab2[T],tab3[T];
srand(time(NULL));
printf("\n");
for (i=0;i<T;i++){
	tab1[i] = rand()%10;
	printf("%d, ",tab1[i]);
}
printf("\n");

for (i=0;i<T;i++){
	tab2[i] = rand()%10;
	printf("%d, ",tab2[i]);
}
printf("\n");
for (i=0;i<T;i++){
	tab3[i] = tab2[i]+ tab1[i];
	printf("%d, ",tab3[i]);
}

printf("\n");



return 0;
}
