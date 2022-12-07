#include <stdio.h>
#include <math.h>
int main(){
float b,c,d;
long double a;
printf("Char: %ld octets %ld bits \n",sizeof(char), 8*sizeof(char));
printf("Unsigned Char: %ld octets %ld bits \n",sizeof(unsigned char), 8*sizeof(unsigned char));
printf("Short: %ld octets %ld bits\n",sizeof(short), 8*sizeof(short));
printf("Unsigned Short: %ld octets %ld bits\n",sizeof(unsigned short), 8*sizeof(unsigned short));
printf("Int: %ld octets %ld bits\n", sizeof(int), 8*sizeof(int));
printf("Unsigned Int: %ld octets %ld bits\n", sizeof(unsigned int), 8*sizeof(unsigned int));
printf("Long: %ld octets %ld bits\n", sizeof(long), 8*sizeof(long));
printf("Unsigned long: %ld octets %ld bits\n", sizeof(unsigned long), 8*sizeof(unsigned long));
printf("Long long: %ld octets %ld bits\n", sizeof(long long ), 8*sizeof(long long));
printf("Unsigned Long long: %ld octets %ld bits\n", sizeof(unsigned long long ), 8*sizeof(unsigned long long));
printf("Float: %ld octets %ld bits\n", sizeof(float), 8*sizeof(float));
printf("Double: %ld octets %ld bits\n", sizeof(double), 8*sizeof(double));
printf("Long Double: %ld octets %ld bits\n", sizeof(long double), 8*sizeof(long double));

a = pow(2,8*sizeof(char));
b=a/2-1;
c = -b;
d=0;
printf("\nIntervalle CHAR [%.0f,%.0f]\n", c,b);



printf("Unsigned Char [%.0f,%.0Lf] \n",d,a-1);

a = pow(2,8*sizeof(short));
b=a/2-1;
c = -b;
d=0;
printf("\nIntervalle Short [%.0f,%.0f]\n", c,b);
printf("Intervalle Unsigned Short [%.0f,%.0Lf]\n", d,a-1);

a = pow(2,8*sizeof(int));
b=a/2-1;
c = -b;
d=0;
printf("\nIntervalle int [%.0f,%.0f]\n", c,b);
printf("Intervalle Unsigned int [%.0f,%.0Lf]\n", d,a-1);

a = pow(2,8*sizeof(long));
b=a/2-1;
c = -b;
d=0;
printf("\nIntervalle long [%.0f,%.0f]\n", c,b);
printf("Intervalle Unsigned long [%.0f,%.0Lf]\n", d,a-1);

a = pow(2,8*sizeof(long long));
b=a/2-1;
c = -b;
d=0;
printf("\nIntervalle long long [%.0f,%.0f]\n", c,b);
printf("Intervalle Unsigned long long [%.0f,%.0Lf]\n", d,a-1);

a = pow(2,8*sizeof(float));
d=0;
printf("\nIntervalle float [%.0f,%.0Lf]\n", d,a-1);

a =pow(2,8*sizeof(double));
d=0;
printf("\nIntervalle double [%.0f,%.0Lf]\n", d,a-1);

a = pow(2,8*sizeof(long double));
d=0;
printf("Intervalle long double [%.0f,%.0Lf]\n", d,a-1);
return 0;
}
