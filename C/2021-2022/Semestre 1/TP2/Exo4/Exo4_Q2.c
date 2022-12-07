#include <stdio.h>
int main (){
int h,i=0,j=0;

do {
 printf("Saisir une hauteur entière ]0, 10[: \n");
 scanf("%d",&h);
}while(h>=10 || h<=0);

for (i=1;i<=h;i++){
	for (j=1;j<i;j++){
		printf("%d",j);
	}
printf("\n");
}

return 0;
}
