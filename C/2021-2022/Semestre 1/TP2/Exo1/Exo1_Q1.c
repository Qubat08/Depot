#include <stdio.h>
int main(){
int a,b,max;
printf("Saisir deux valeurs: \n");
scanf("%d %d",&a,&b);
if (a>b){
 max =a;
}
else{ max =b;}
printf("Le maximum est %d \n",max);

//max = a>b ? a:b;

return 0;
}
