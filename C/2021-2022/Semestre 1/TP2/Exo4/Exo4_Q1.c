#include <stdio.h>
int main (){
double i=0;
double c=0;
double f=0;

printf(" F ******* C ******* F\n");
while (i<=300){
	c = (i-32)*5/9;
	f = (c*9/5) +32;
	printf("%.0lf ******* %.2lf ******* %.0lf  \n",i,c,f);
	i=i+20;
}

return 0;
}
