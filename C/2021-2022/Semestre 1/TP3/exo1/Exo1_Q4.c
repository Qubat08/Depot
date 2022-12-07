#include <stdio.h>
int main (){
double x;
long int res;

scanf("%lf",&x);

if ((x < -2147483647)||(x> 2147483647)){
 res = -1;
}
else{
 res = (long int)x;
}

printf("%ld \n",res);



return 0;
}
